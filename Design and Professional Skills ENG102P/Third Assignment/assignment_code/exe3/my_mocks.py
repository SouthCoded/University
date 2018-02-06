#########
# Mocks #
#########

# TODO: implement here the mocks that enable the tests in tail_reader_test.py to run

# class FakeFileHandler:
#     def __init__(self,content):
#          self.assert_called_with = "HO"
#     def assert_called_with():
#     	print("HEY")

class FakeFileHandler:
    def __init__(self, arg):
    	self.arg = arg
    def stat(self,stat):
       return stat
    # def st_size(self):
    # 	return ''


class FakeFileReader:
    def __init__(self):
         self.content = "HO"
    def assert_called_with(self,data,filename,numlines,stopline,bufsize):
       return ''

    def __next__(self):
    	return ''

	

def fake_get_filesize(self):
	return 5