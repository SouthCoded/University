import sys, asyncio

################
# Server class #
################

class Server:
    default_server_address = '127.0.0.1'
    default_server_port = 8888

    # NOTE: you can modify __init__
    def __init__(self,server_address=default_server_address,server_port=default_server_port):
        self.address = server_address
        self.port = server_port
        self.all_clients = set([])
        self.address2name = {}

    # NOTE: the following method must be implemented for some of our grading tests to work. If you don't implement this method correctly, you will lose some marks!
    # method for registering usernames 
    def set_username(self,new_username,writer,old_username=None):
        self.address2name[writer.get_extra_info('peername')] = new_username
        self.new_username = new_username

    # NOTE: this method must be implemented for some of our grading tests to work. If you don't implement this method correctly, you will lose some marks!
    # method that returns all the registered usernames as a list
    def get_registered_usernames_list(self):
        return self.address2name

    # NOTE: you can modify the implementation of handle_connection (but not its signature)
    @asyncio.coroutine
    def handle_connection(self, reader, writer):
        self.all_clients.add(writer)
        client_addr = writer.get_extra_info('peername')
        print('New client {}'.format(client_addr))
        self.set_username("",writer)

        while True:

            data = yield from reader.read(100)
            if data == None or len(data) == 0:
                break
            message = data.decode()
            print("Received {} from {}".format(message, client_addr))

            if "@server" in message:
                if "set_my_id" in message:
                    add2name = self.get_registered_usernames_list()
                    if message[18:-1] not in add2name.values():
                        self.set_username(message[18:-1],writer)
                        mes = "@client username set to " + str(message[18:-1])
                        writer.write(mes.encode())
                    else:
                        mes = "@client ERROR <Duplicate Name>"
                        writer.write(mes.encode())
                else:
                    mes = "@client ERROR does not match username standards"
                    writer.write(mes.encode())

            elif self.address2name[writer.get_extra_info('peername')] == '':
                mes = "@client ERROR not registered"
                writer.write(mes.encode())


            for other_writer in self.all_clients:

                if other_writer != writer:

                    name = self.address2name[writer.get_extra_info('peername')]

                    if name is not '':
                        if "@" in message:
                            if "client" not in message:
                                if "server" not in message:
                                    temp = message.split(" ",1)
                                    desired_user = temp[0][1:]
                                    add2name = self.get_registered_usernames_list()
                                    for x in add2name.keys():
                                        if add2name[x] == desired_user:
                                            if x == other_writer.get_extra_info('peername'):
                                                msg = "[private] " + name + " : " + temp[1]
                                                other_writer.write(msg.encode())
                                                yield from other_writer.drain()   

                        else:
                            other_writer.write(("@" + name + " " + message).encode())
                            yield from other_writer.drain()   

        print("Closing connection with client {}".format(client_addr))
        writer.close()
        self.all_clients.remove(writer)

    # NOTE: do not modify run
    def run(self):
        loop = asyncio.get_event_loop()
        coro = asyncio.start_server(self.handle_connection,self.address,
                                                    self.port,loop=loop)
        server = loop.run_until_complete(coro)

        print('Serving on {}'.format(server.sockets[0].getsockname()))
        try:
            loop.run_forever()
        except KeyboardInterrupt:
            print('\nGot keyboard interrupt, shutting down',file=sys.stderr)
        
        for task in asyncio.Task.all_tasks():
            task.cancel()
        server.close()
        loop.run_until_complete(server.wait_closed())
        loop.close()    


# NOTE: do not modify the following two lines
if __name__ == '__main__':
    Server().run()

