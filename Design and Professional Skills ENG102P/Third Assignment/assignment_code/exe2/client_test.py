import io, pytest, asyncio, mock, aioconsole
import client

#########
# Mocks #
#########

class FakeReader:
    def __init__(self,predefined_content_list,output_pace=0.1):
        self.delay = output_pace
        if predefined_content_list == None:
            self.messages = None
        else:
            self.messages = list(predefined_content_list)

    @asyncio.coroutine
    def read(self, length):
        yield from asyncio.sleep(self.delay)
        if self.messages == None:
            return None
        if len(self.messages) > 0:
            m = self.messages.pop(0)
            if m == None:
                return None
            return m.encode()
        return ''

class FakeTransport:
    def __init__(self):
        self.closed = False

    def close(self):
        self.closed = True
        
    def is_closing(self):
        return self.closed

class FakeWriter:
    def __init__(self):
        self.writer = io.BytesIO()
        self.transport = FakeTransport()
        self.open()

    def write(self, data):
        return self.writer.write(data)

    def getvalue(self):
        return self.writer.getvalue()

    def close(self):
        self.closed = True
        self.transport.close()
    
    def open(self):
        self.closed = False

    def is_closed(self):
        return self.closed

class FakeConsole:
    def __init__(self,predefined_content=[],output_pace=0,final_message='close()'):
        self.delay = output_pace
        if predefined_content == None:
            self.messages = None
        else:
            self.messages = list(predefined_content)
        self.final_string = final_message
    
    @asyncio.coroutine
    def fake_console_read(self,prompt):
        yield from asyncio.sleep(self.delay)
        if self.messages == None:
            return None
        if len(self.messages) > 0:
            return self.messages.pop(0)
        else:
            return self.final_string

#########
# Tests #
#########

class TestCorrectedClientClass:
    def setup_method(self,method):
        self.loop = asyncio.get_event_loop()        
        self.fake_writer = FakeWriter()
        self.testclient = client.Client()

    # Check handling of interleaved read and write
    # (client should read everything before the user closes)
    def test_interleaved_messages(self,capsys):
        reader_messages = ['Hello World!','That\'s all folks']
        fake_reader = FakeReader(reader_messages)
        console_messages = []
        fake_console = FakeConsole(console_messages,output_pace=0.2)

        with mock.patch('aioconsole.ainput',side_effect=\
                fake_console.fake_console_read) as mock_console:
            self.loop.run_until_complete(self.testclient.use_connection(fake_reader, self.fake_writer))

        assert mock_console.call_count == len(console_messages) + 1
        out, err = capsys.readouterr()
        for message in console_messages:
            assert message.encode() in self.fake_writer.getvalue()
            assert '[public] %r' % message in out
        assert 'Got close() from user.' in out
        assert len(err) == 0

    # Check handling of multiple messages 
    def test_exchange_two_messages(self,capsys):
        messages = ['Hello World!','That\'s all folks']
        fake_reader = FakeReader(messages)
        fake_console = FakeConsole(messages,output_pace=0.2)
        with mock.patch('aioconsole.ainput',side_effect=\
                fake_console.fake_console_read) as mock_console:
            self.loop.run_until_complete(self.testclient.use_connection(fake_reader, self.fake_writer))
        assert mock_console.call_count == len(messages) + 1
        out, err = capsys.readouterr()
        for message in messages:
            assert message.encode() in self.fake_writer.getvalue()
            assert '[public] %s' % message in out
        assert 'Got close() from user.' in out
        assert len(err) == 0

    # Check that the client sends out the exact input message
    # and that it prints exactly what the server answers
    def test_happy_path_one_message(self,capsys):
        message = 'Hello World!'
        fake_reader = FakeReader([message])
        fake_console = FakeConsole([message],output_pace=0.2)
        with mock.patch('aioconsole.ainput',side_effect=fake_console.fake_console_read)\
                as mock_console:
            self.loop.run_until_complete(
                self.testclient.use_connection(fake_reader, self.fake_writer))
        assert mock_console.call_count == 2
        assert self.fake_writer.getvalue() == message.encode()
        assert self.fake_writer.is_closed()
        out, err = capsys.readouterr()
        assert '[public] %s' % message in out.strip()
        assert 'Got close() from user' in out.strip()
        assert len(err) == 0

    # Check that the client does not send any None message 
    def test_none_messages(self,capsys):
        message = None
        fake_reader = FakeReader([],output_pace=0.1)
        fake_console = FakeConsole([message])
        with mock.patch('aioconsole.ainput',side_effect=fake_console.fake_console_read)\
                as mock_console:
            self.loop.run_until_complete(
                self.testclient.use_connection(fake_reader, self.fake_writer))
        assert mock_console.call_count == 2
        assert len(self.fake_writer.getvalue()) == 0
        out, err = capsys.readouterr()
        assert 'Got close() from user.' in out
        assert 'Terminating read from network.' in out
        assert len(err) == 0

    # Check that the client does not send any empty message 
    def test_happy_path_empty_console_message(self,capsys):
        message = ''
        fake_reader = FakeReader([message],output_pace=0.1)
        fake_console = FakeConsole([message])
        with mock.patch('aioconsole.ainput',side_effect=fake_console.fake_console_read)\
                as mock_console:
            self.loop.run_until_complete(
                self.testclient.use_connection(fake_reader, self.fake_writer))
        assert mock_console.call_count == 2
        assert len(self.fake_writer.getvalue()) == 0
        out, err = capsys.readouterr()
        assert 'Got close() from user.' in out
        assert 'Terminating read from network.' in out
        assert len(err) == 0

    # Check that the client does close as expected, when the user 
    # asks to do so
    def test_happy_path_close_from_user(self,capsys):
        fake_reader = FakeReader([])
        fake_console = FakeConsole([])
        with mock.patch('aioconsole.ainput',side_effect=fake_console.fake_console_read)\
                as mock_console:
            self.loop.run_until_complete(
                self.testclient.use_connection(
                    fake_reader, self.fake_writer))
        assert mock_console.call_count == 1
        assert len(self.fake_writer.getvalue()) == 0
        assert self.fake_writer.is_closed()
        out, err = capsys.readouterr()
        assert 'Got close() from user' in out.strip()
        assert len(err) == 0

    # Opening a connection towards a closed IP address and port
    # should raise no exception, and print a message on stderr
    def test_failed_open_connection(self,capsys):
        self.testclient.run()
        out, err = capsys.readouterr()
        assert len(out) == 0
        assert '[Errno 111] Connect call failed' in err


   
