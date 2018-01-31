import sys, asyncio

all_clients = set([])

# NOTE: do not modify the current lines in handle_connection, but you can add others
@asyncio.coroutine
def handle_connection(reader, writer):
    all_clients.add(writer)
    client_addr = writer.get_extra_info('peername')
    print('New client {}'.format(client_addr))
    while True:
        data = yield from reader.read(100)
        if data == None or len(data) == 0:
            break
        message = data.decode()
        print("Received {} from {}".format(message, client_addr))
        for other_writer in all_clients:
            if other_writer != writer:
                new_message = '{} says: {}'.format(client_addr,data)
                other_writer.write(new_message.encode())
                yield from other_writer.drain()
    all_clients.remove(writer)
    print("Close the client socket")
    yield from writer.drain()
    writer.close()

# NOTE: do not modify the run function
def run():
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle_connection,'127.0.0.1',
                                                8888,loop=loop)
    server = loop.run_until_complete(coro)

    # Serve requests until Ctrl+C is pressed
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

if __name__ == '__main__':
    run()

