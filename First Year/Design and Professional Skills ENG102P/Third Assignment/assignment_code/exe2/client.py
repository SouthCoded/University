import sys, asyncio
import aioconsole

#####################
# Custom exceptions #
#####################

class NoneException(Exception):
    pass

class ClosingException(Exception):
    pass

################
# Client class #
################

class Client:
    default_server_address = '127.0.0.1'
    default_server_port = 8888

    # NOTE: you can modify __init__
    def __init__(self, server_address=default_server_address, server_port=default_server_port):
        self.server_address = server_address
        self.server_port = server_port
        self.name = None                    # NOTE: do not remove the attribute from your client implementation, but use it to store the registered username associated to this client. This is a pre-condition for some of our grading tests to work correctly.


    # NOTE: do not modify open_connection
    @asyncio.coroutine
    def open_connection(self,loop):
        reader, writer = yield from asyncio.open_connection(
                        self.server_address, self.server_port, loop=loop)
        return reader, writer
    
    # NOTE: do not modify use_connection
    @asyncio.coroutine
    def use_connection(self,reader, writer):
        yield from asyncio.gather(self.read_from_network(reader,writer),
                                            self.send_to_server(writer))

    # NOTE: you can modify the implementation of read_from_network (but not its signature)
    @asyncio.coroutine
    def read_from_network(self,reader,writer):
        while True:
            net_message = yield from reader.read(100)

            if writer.transport.is_closing():
                print('Terminating read from network.')
                break
            elif net_message == None:
                continue
            elif len(net_message) == 0:
                print('The server closed the connection.')
                writer.close()
                break
            elif "@client" in net_message.decode():
                print("[server]" + net_message.decode()[7:])
                if "username set" in net_message.decode():
                    self.name = net_message.decode()[24:]
                print('>> ',end='',flush=True)
            elif "[private]" in net_message.decode():
                print(net_message.decode())
                print('>> ',end='',flush=True)
            else:
                temp = net_message.decode().split(" ",1)
                if '@' in temp[0]:
                    print("[public] " + temp[0][1:] + " : " + temp[1])
                    print('>> ',end='',flush=True)
                else:
                    print("[public] " + temp[0] + " " + temp[1])
                    print('>> ',end='',flush=True)


    # NOTE: you can modify the implementation of send_to_server (but not its signature)
    @asyncio.coroutine
    def send_to_server(self,writer):
        try:
            while True:
                original_message = yield from aioconsole.ainput('>> ')
                if original_message != None:
                    console_message = original_message.strip()
           
                    if console_message == '':
                        continue
                    elif console_message == 'close()':
                        raise ClosingException()
                    
                    elif "@server set_my_id" in console_message:
                        if " " in console_message[18:-1]:
                            print("[error] <Invalid character>")
                        elif "client" in console_message[18:-1]:
                            print("[error] <Invalid name>")
                        elif "server" in console_message[18:-1]:
                            print("[error] <Invalid name>")
                        else:
                            msg = console_message
                            writer.write(msg.encode())
                    elif self.name is not None:
                        temp = "@" + str(self.name)
                        if temp in console_message:
                            print("[error] <Private message to yourself")
                        else:
                            msg = console_message
                            writer.write(msg.encode())
                    else:
                        msg = console_message
                        writer.write(msg.encode())

        except ClosingException:
            print('Got close() from user.')
        finally:
            if not writer.transport.is_closing():
                writer.close()

    # NOTE: do not modify run
    def run(self):
        try:
            loop = asyncio.get_event_loop()
            reader,writer=loop.run_until_complete(self.open_connection(loop))
            loop.run_until_complete(self.use_connection(reader,writer))
        except KeyboardInterrupt:
            print('Got Ctrl-C from user.')
        except Exception as e:
            print(e,file=sys.stderr)
        finally:
            loop.close()

# NOTE: do not modify the following two lines
if __name__ == '__main__':
    Client().run()

