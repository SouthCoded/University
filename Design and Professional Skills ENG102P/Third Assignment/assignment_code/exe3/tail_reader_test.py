import sys, math, mock
import my_mocks
import tail_reader

# NOTE: do not add, remove or change any line of code to this file -- except temporary instructions (to be removed before the submission) you might need to understand the code.

#########
# Tests #
#########

class TestTailReaderWithMockClass:
    def setup_method(self,method):
        self.treader = tail_reader.TailReader()
        self.fake_content = 'line1\nline2\nline3\nline4'
        self.fake_handler = my_mocks.FakeFileHandler(self.fake_content)
        self.fake_reader = my_mocks.FakeFileReader()

    def test_bufsize_impact(self,capsys):
        test_bufsize = 2
        test_filesize = my_mocks.fake_get_filesize(None)
        with mock.patch('builtins.open') as mock_open,\
             mock.patch('tail_reader.TailReader.get_file_size',side_effect=my_mocks.fake_get_filesize) as mock_get_size,\
             mock.patch('tail_reader.TailReader.read_new_data') as mock_read_data:
            result = self.treader.read_file_from_tail([],'',sys.maxsize,None,test_bufsize)
        assert len(result) == 0
        assert mock_open.call_count == 1
        assert mock_get_size.call_count == 1
        assert mock_read_data.call_count == math.floor(test_filesize / test_bufsize)
        out, err = capsys.readouterr()
        print(out)
        assert len(out) == 0
        assert len(err) == 0

    def test_set_right_parameters_for_get_text(self,capsys):
        with mock.patch('tail_reader.TailReader.read_file_from_tail',side_effect=self.fake_reader) as mock_read:
            self.treader.get_text(None,stopline='we should stop here')
        self.fake_reader.assert_called_with([],None,sys.maxsize,'we should stop here\n',8192)

    def test_read_file_from_tail_no_limits(self,capsys):
        with mock.patch('builtins.open',return_value=self.fake_handler) as mock_open,\
             mock.patch('os.stat',side_effect=self.fake_handler.stat) as mock_stat:
            result = self.treader.read_file_from_tail([],'',sys.maxsize,None,100)
        lines = result.split('\n')
        assert len(result) == len(self.fake_content)
        assert result == self.fake_content
        out, err = capsys.readouterr()
        assert len(out) == 0
        assert len(err) == 0

