## COMP0019 CW2 Grade Report
Graded at: 2020-01-28 15:14:10.953531

Report for commit SHA: 50a59c57f5e0fbc7e8fc0928e025146893a084f8

### Output


    CLEAN 
      COMPILE cs0019.c
      COMPILE basealloc.c
      COMPILE test001.c
      LINK test001 
      COMPILE test002.c
      LINK test002 
      COMPILE test003.c
      LINK test003 
      COMPILE test004.c
      LINK test004 
      COMPILE test005.c
      LINK test005 
      COMPILE test006.c
      LINK test006 
      COMPILE test007.c
      LINK test007 
      COMPILE test008.c
      LINK test008 
      COMPILE test009.c
      LINK test009 
      COMPILE test010.c
      LINK test010 
      COMPILE test011.c
      LINK test011 
      COMPILE test012.c
      LINK test012 
      COMPILE test013.c
      LINK test013 
      COMPILE test014.c
      LINK test014 
      COMPILE test015.c
      LINK test015 
      COMPILE test016.c
      LINK test016 
      COMPILE test017.c
      LINK test017 
      COMPILE test018.c
      LINK test018 
      COMPILE test019.c
      LINK test019 
      COMPILE test020.c
      LINK test020 
      COMPILE test021.c
      LINK test021 
      COMPILE test022.c
      LINK test022 
      COMPILE test023.c
      LINK test023 
      COMPILE test024.c
      LINK test024 
      COMPILE test025.c
      LINK test025 
      COMPILE test026.c
      LINK test026 
      COMPILE test027.c
      LINK test027 
      COMPILE test028.c
      LINK test028 
      COMPILE test029.c
      LINK test029 
      COMPILE test030.c
      LINK test030 
      COMPILE test031.c
      LINK test031 
      COMPILE test032.c
      LINK test032 
      COMPILE test033.c
      LINK test033 
      COMPILE test034.c
      LINK test034 
      COMPILE test035.c
      LINK test035 
      COMPILE test036.c
      LINK test036 
      COMPILE test037.c
      LINK test037 
      COMPILE test038.c
      LINK test038 
      COMPILE hhtest.c
      LINK hhtest 
    *** Run 'make check' or 'make check-all' to check your work.
    test001 OK
    test002 OK
    test003 OK
    test004 OK
    test005 OK
    test006 OK
    test007 OK
    test008 OK
    test009 OK
    test010 OK
    test011 OK
    test012 OK
    test013 OK
    test014 OK
    test015 OK
    test016 OK
    test017 OK
    test018 OK
    test019 OK
    test020 OK
    test021 OK
    test022 OK
    test023 OK
    test024 OK
    test025 OK
    test026 OK
    test027 OK
    test028 OK
    test029 OK
    test030 OK
    test031 OK
    test032 OK
    test033 OK
    test034 OK
    test035 OK
    test036 OK
    test037 OK
    test038 OK
    All tests passed!
    make: 'hhtest' is up to date.
    ./hhtest 0
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001df1028 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7fd4eadc07e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7fd4eadc937a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7fd4eadcd53c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7fd4ead69830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00603000-00604000 r--p 00003000 08:01 422594                             /home/user/hhtest
    00604000-00605000 rw-p 00004000 08:01 422594                             /home/user/hhtest
    01df1000-01e12000 rw-p 00000000 00:00 0                                  [heap]
    7fd4e4000000-7fd4e4021000 rw-p 00000000 00:00 0 
    7fd4e4021000-7fd4e8000000 ---p 00000000 00:00 0 
    7fd4eab33000-7fd4eab49000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fd4eab49000-7fd4ead48000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fd4ead48000-7fd4ead49000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fd4ead49000-7fd4eaf09000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fd4eaf09000-7fd4eb109000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fd4eb109000-7fd4eb10d000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fd4eb10d000-7fd4eb10f000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fd4eb10f000-7fd4eb113000 rw-p 00000000 00:00 0 
    7fd4eb113000-7fd4eb21b000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fd4eb21b000-7fd4eb41a000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fd4eb41a000-7fd4eb41b000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fd4eb41b000-7fd4eb41c000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fd4eb41c000-7fd4eb442000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fd4eb62f000-7fd4eb632000 rw-p 00000000 00:00 0 
    7fd4eb63e000-7fd4eb641000 rw-p 00000000 00:00 0 
    7fd4eb641000-7fd4eb642000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fd4eb642000-7fd4eb643000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fd4eb643000-7fd4eb644000 rw-p 00000000 00:00 0 
    7fff0a16f000-7fff0a190000 rw-p 00000000 00:00 0                          [stack]
    7fff0a1c8000-7fff0a1ca000 r--p 00000000 00:00 0                          [vvar]
    7fff0a1ca000-7fff0a1cc000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    Aborted
    
    ========================
    ./hhtest 1
    Segmentation fault
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest 0.4
    Segmentation fault
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest -0.4
    Segmentation fault
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest -l
    Segmentation fault
    timeout: the monitored command dumped core
    hhtests complete. Check the results to see if they look OK.
    


### Marking

Heavy hitter marks: 0/20

Total score: (38/38) * 80.0 + 0 = 80/100

