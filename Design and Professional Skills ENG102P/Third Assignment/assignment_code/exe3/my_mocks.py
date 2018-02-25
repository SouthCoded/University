#########
# Mocks #
#########

# TODO: implement here the mocks that enable the tests in tail_reader_test.py to run

class FakeFileHandler:
    
    def __init__(self,content):
        self.content = content

    def seek(self,offset = 0):
        pass

    def stat(self,arg):
        obj = os()
        return obj

    def readlines(self):
        return self.content

    def __enter__(self):
        return self

    def __exit__(self,second,third,fourth):
        pass

class os:
    def __init__(self):
        self.st_size = 10

class FakeFileReader:

    def __next__(self):
        return ''
    def assert_called_with(self,data,filename,numlines,stopline,bufsize):
       return ''

def fake_get_filesize(self):
	return 10

