## COMP0019 CW3 Grade Report
Graded at : 2020-02-17 16:18:15.939402
Report for commit SHA: e6ad2d62f19d02707aa5ffa9d3622eb8092e2c96

### Output


    -- The C compiler identification is GNU 5.4.0
    -- The CXX compiler identification is GNU 5.4.0
    -- Check for working C compiler: /usr/bin/cc
    -- Check for working C compiler: /usr/bin/cc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Setting build type to 'Debug' as none was specified.
    -- Looking for C++ include unistd.h
    -- Looking for C++ include unistd.h - found
    -- Looking for C++ include stdint.h
    -- Looking for C++ include stdint.h - found
    -- Looking for C++ include inttypes.h
    -- Looking for C++ include inttypes.h - found
    -- Looking for C++ include sys/types.h
    -- Looking for C++ include sys/types.h - found
    -- Looking for C++ include sys/stat.h
    -- Looking for C++ include sys/stat.h - found
    -- Looking for C++ include fnmatch.h
    -- Looking for C++ include fnmatch.h - found
    -- Looking for C++ include stddef.h
    -- Looking for C++ include stddef.h - found
    -- Check size of uint32_t
    -- Check size of uint32_t - done
    -- Looking for strtoll
    -- Looking for strtoll - found
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/user/build
    Scanning dependencies of target gene_encode
    [  7%] Building C object CMakeFiles/gene_encode.dir/src/comp0019lib.c.o
    [ 14%] Building C object CMakeFiles/gene_encode.dir/src/comp0019.c.o
    [ 21%] Building C object CMakeFiles/gene_encode.dir/src/decomp0019.c.o
    [ 28%] Linking C static library libgene_encode.a
    [ 28%] Built target gene_encode
    Scanning dependencies of target encode
    [ 35%] Building C object CMakeFiles/encode.dir/src/encode.c.o
    [ 42%] Linking C executable encode
    [ 42%] Built target encode
    Scanning dependencies of target gflags_nothreads_static
    [ 50%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags.cc.o
    [ 57%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags_reporting.cc.o
    [ 64%] Building CXX object external/gflags/CMakeFiles/gflags_nothreads_static.dir/src/gflags_completions.cc.o
    [ 71%] Linking CXX static library libgflags_nothreads.a
    [ 71%] Built target gflags_nothreads_static
    Scanning dependencies of target lzw_test
    [ 78%] Building CXX object CMakeFiles/lzw_test.dir/src/lzw_test.cc.o
    [ 85%] Linking CXX executable lzw_test
    [ 85%] Built target lzw_test
    Scanning dependencies of target decode
    [ 92%] Building C object CMakeFiles/decode.dir/src/decode.c.o
    [100%] Linking C executable decode
    [100%] Built target decode
    Scanning dependencies of target test-all
    Test group one (all possible sequences with N elements):
    testing encode for 4 sequences of size 1: OK
    testing decode for 4 sequences of size 1: OK
    testing encode for 16 sequences of size 2: OK
    testing decode for 16 sequences of size 2: OK
    testing encode for 64 sequences of size 3: OK
    testing decode for 64 sequences of size 3: OK
    testing encode for 256 sequences of size 4: OK
    testing decode for 256 sequences of size 4: OK
    testing encode for 1024 sequences of size 5: OK
    testing decode for 1024 sequences of size 5: OK
    testing encode for 4096 sequences of size 6: OK
    testing decode for 4096 sequences of size 6: OK
    Group one score: 12/12
    
    Test group two (pre-generated random sequences of size N):
    testing encode for sequence of size 1: OK
    testing decode for sequence of size 1: OK
    testing encode for sequence of size 4: OK
    testing decode for sequence of size 4: OK
    testing encode for sequence of size 16: OK
    testing decode for sequence of size 16: OK
    testing encode for sequence of size 64: OK
    testing decode for sequence of size 64: OK
    testing encode for sequence of size 256: OK
    testing decode for sequence of size 256: OK
    testing encode for sequence of size 1024: OK
    testing decode for sequence of size 1024: OK
    testing encode for sequence of size 4096: OK
    testing decode for sequence of size 4096: OK
    testing encode for sequence of size 16384: OK
    testing decode for sequence of size 16384: OK
    Group two score: 16/16
    
    Test group three (invalid inputs):
    testing encode for invalid encoder inputs: OK
    testing decode for invalid decoder inputs: OK
    Group three score: 2/2
    
    [100%] Built target test-all


### Marking

Total score: (12 / 12) * 35 + (16 / 16) * 35 + (2 / 2) * 30 = 100 / 100

