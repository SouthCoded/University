import sys, asyncio
import aioconsole

#####################
# Custom exceptions #
#####################

class NoneException(Exception):
    pass

class ClosingException(Exception):
    pass

#################################
# Network interaction functions #
#################################

# NOTE: do not modify open_connection
@asyncio.coroutine
def open_connection(loop):
    reader, writer = yield from asyncio.open_connection('127.0.0.1',
                                                     8888,loop=loop)
    return reader, writer

# NOTE: do not modify open_connection
@asyncio.coroutine
def use_connection(reader, writer):
    yield from asyncio.gather(read_from_network(reader,writer),
                                        send_to_server(writer))

# NOTE: you can modify the implementation of read_from_network (but not its signature)
@asyncio.coroutine
def read_from_network(reader,writer):
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
            #sys.exit()
            break
        print('\nReceived: %r' % net_message.decode())
        print('>> ',end='',flush=True)
        
# NOTE: you can modify the implementation of send_to_server (but not its signature)
@asyncio.coroutine
def send_to_server(writer):
    try:
        while True:
            original_message = yield from aioconsole.ainput('>> ')
            if original_message != None:
                console_message = original_message.strip()
                if console_message == '':
                    continue
                if console_message == 'close()' or \
                            writer.transport.is_closing():
                    raise ClosingException()
                writer.write(console_message.encode())
    except ClosingException:
        print('Got close() from user.')
    finally:
        loop = asyncio.get_event_loop()
        if not loop.is_closed():
            if not writer.transport.is_closing():
                writer.close()


##################
# Main functions #
##################

# NOTE: do not modify the current lines in run, but you can add others
def run():
    try:
        loop = asyncio.get_event_loop()
        reader,writer=loop.run_until_complete(open_connection(loop))
        loop.run_until_complete(use_connection(reader,writer))
    except KeyboardInterrupt:
        print('Got Ctrl-C from user.')
    except Exception as e:
        print(e,file=sys.stderr)
    finally:
        loop.close()


if __name__ == '__main__':
    run()

