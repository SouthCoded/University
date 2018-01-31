import os, sys

# NOTE: do not add, remove or change any line of code to this file -- except temporary instructions (to be removed before the submission) you might need to understand the code.

class TailReader:
    
    # helper methods
    def get_file_size(self,filename):
        return os.stat(filename).st_size
        
    def read_new_data(self,filehandler,offset,data):
        filehandler.seek(offset)
        data.extend(filehandler.readlines())

    def get_output_from_read(self,data,starting_index):
        return ''.join(data[starting_index:]).strip()

    # the method computes the index of the last occurrence of stopline, as offset from the end of the data list
    def get_last_occurrence_stopline(self,stopline,data):
        data_copy = list(data)
        data_copy.reverse()
        return data_copy.index(stopline)+1

    # the method reads a file from the last "block" to the first one: it will stop when reaching a given stopline or reading an input number of lines. Default values of the input parameters make the method read the whole file. 
    def read_file_from_tail(self,data,filename,numlines,stopline,bufsize):
        fsize = self.get_file_size(filename)
        it = 0
        with open(filename) as f:
            if bufsize > fsize:
                bufsize = fsize-1
            while True:
                it += 1
                new_offset = max(fsize - bufsize*it,0)
                if new_offset < bufsize:
                    new_offset = 0
                self.read_new_data(f,new_offset,data)
                if len(data) >= numlines:
                    return self.get_output_from_read(data,-numlines)
                elif stopline != None and stopline in data:
                    pos_from_data_end = self.get_last_occurrence_stopline(stopline,data)
                    return self.get_output_from_read(data,-pos_from_data_end)
                elif new_offset == 0:
                    return self.get_output_from_read(data,0)

    # main method, adjusting parameters to be passed to read_file_from_tail
    def get_text(self,filename,numlines=sys.maxsize,stopline=None):
        try:
            initial_data = []
            bufsize = 8192
            if stopline != None:
                stopline = stopline+"\n"
            return self.read_file_from_tail(initial_data,filename,numlines,stopline,bufsize)
        except FileNotFoundError:
            print('No file called %r' %(filename))
            return None
