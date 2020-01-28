## COMP0019 CW2 Grade Report
Graded at: 2020-01-26 15:16:53.525477

Report for commit SHA: b41c4f115a583eaa987a9f554d84ff46d0ca3e43

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
    test020 FAIL: Unexpected output starting on line 1
      test020.c:14: Expected `MEMORY BUG???: invalid free of pointer ???`
      output:1: Got `malloc count: active 18446744073709551615   total          1   fail          0
                     malloc size:  active 18446744073709549615   total       2001   fail          0`
    test021 FAIL: Unexpected output starting on line 1
      test021.c:13: Expected `MEMORY BUG???: invalid free of pointer ???, not allocated`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active       2001   total       2001   fail          0`
    test022 FAIL: Unexpected output starting on line 1
      test022.c:13: Expected `MEMORY BUG: test???.c:9: invalid free of pointer ???, not allocated`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active       2001   total       2001   fail          0`
    test023 FAIL: Unexpected output starting on line 1
      test023.c:13: Expected `MEMORY BUG: test???.c:9: invalid free of pointer ???, not allocated`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active       2001   total       2001   fail          0`
    test024 OK
    test025 FAIL: Unexpected output starting on line 1
      test025.c:13: Expected `MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???`
      output:1: Got `malloc count: active          1   total          2   fail          0
                     malloc size:  active       4001   total       4001   fail          0`
    test026 FAIL: Missing output starting on line 0
      test026.c:13: Expected `MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???`
    test027 FAIL: Unexpected output starting on line 1
      test027.c:13: Expected `MEMORY BUG???: invalid ??{realloc|free}?? of pointer ???`
      output:1: Got `malloc count: active          1   total          2   fail          0
                     malloc size:  active       4005   total       4005   fail          0`
    test028 FAIL: Unexpected output starting on line 1
      test028.c:16: Expected `MEMORY BUG???: detected wild write during free of pointer ???`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active          0   total         40   fail          0`
    test029 FAIL: Unexpected output starting on line 1
      test029.c:17: Expected `MEMORY BUG???: detected wild write during free of pointer ???`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active          0   total         63   fail          0`
    test030 FAIL: Unexpected output starting on line 1
      test030.c:16: Expected `MEMORY BUG???: detected wild write during free of pointer ???`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active          0   total          3   fail          0`
    test031 OK
    test032 FAIL: Missing output starting on line 1
      test032.c:40: Expected `LEAK CHECK: test???.c:18: allocated object ??pointer?? with size ??size??`
    test033 FAIL: Missing output starting on line 0
      test033.c:31: Expected `LEAK CHECK: test???.c:10: allocated object ??{\w+}?? with size 11`
    test034 FAIL: Unexpected output starting on line 1
      test034.c:13: Expected `MEMORY BUG: test???.c:9: invalid free of pointer ???, not allocated`
      output:1: Got `malloc count: active          0   total          1   fail          0
                     malloc size:  active       2001   total       2001   fail          0`
    test035 FAIL: Unexpected output starting on line 1
      test035.c:18: Expected `MEMORY BUG???: invalid free of pointer ???, not allocated`
      output:1: Got `malloc count: active          3   total          4   fail          0
                     malloc size:  active       3400   total       3450   fail          0`
    test036 FAIL: Unexpected output starting on line 1
      test036.c:20: Expected `MEMORY BUG???: ??? free of pointer ???`
      output:1: Got `malloc count: active          2   total          4   fail          0
                     malloc size:  active       3350   total       3450   fail          0`
    test037 OK
    test038 OK
    23 of 38 tests passed
    make: 'hhtest' is up to date.
    ./hhtest 0
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001ac5018 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7fae998147e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7fae9981d37a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7fae9982153c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7fae997bd830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01ac5000-01ae6000 rw-p 00000000 00:00 0                                  [heap]
    7fae94000000-7fae94021000 rw-p 00000000 00:00 0 
    7fae94021000-7fae98000000 ---p 00000000 00:00 0 
    7fae99587000-7fae9959d000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fae9959d000-7fae9979c000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fae9979c000-7fae9979d000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7fae9979d000-7fae9995d000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fae9995d000-7fae99b5d000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fae99b5d000-7fae99b61000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fae99b61000-7fae99b63000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7fae99b63000-7fae99b67000 rw-p 00000000 00:00 0 
    7fae99b67000-7fae99c6f000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fae99c6f000-7fae99e6e000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fae99e6e000-7fae99e6f000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fae99e6f000-7fae99e70000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7fae99e70000-7fae99e96000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fae9a083000-7fae9a086000 rw-p 00000000 00:00 0 
    7fae9a092000-7fae9a095000 rw-p 00000000 00:00 0 
    7fae9a095000-7fae9a096000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fae9a096000-7fae9a097000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7fae9a097000-7fae9a098000 rw-p 00000000 00:00 0 
    7fff0ec35000-7fff0ec56000 rw-p 00000000 00:00 0                          [stack]
    7fff0ed12000-7fff0ed14000 r--p 00000000 00:00 0                          [vvar]
    7fff0ed14000-7fff0ed16000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    Aborted
    
    ========================
    ./hhtest 1
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001eef018 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f27b31687e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f27b317137a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f27b317553c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f27b3111830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01eef000-01f10000 rw-p 00000000 00:00 0                                  [heap]
    7f27ac000000-7f27ac021000 rw-p 00000000 00:00 0 
    7f27ac021000-7f27b0000000 ---p 00000000 00:00 0 
    7f27b2edb000-7f27b2ef1000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f27b2ef1000-7f27b30f0000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f27b30f0000-7f27b30f1000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f27b30f1000-7f27b32b1000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f27b32b1000-7f27b34b1000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f27b34b1000-7f27b34b5000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f27b34b5000-7f27b34b7000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f27b34b7000-7f27b34bb000 rw-p 00000000 00:00 0 
    7f27b34bb000-7f27b35c3000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f27b35c3000-7f27b37c2000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f27b37c2000-7f27b37c3000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f27b37c3000-7f27b37c4000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f27b37c4000-7f27b37ea000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f27b39d7000-7f27b39da000 rw-p 00000000 00:00 0 
    7f27b39e6000-7f27b39e9000 rw-p 00000000 00:00 0 
    7f27b39e9000-7f27b39ea000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f27b39ea000-7f27b39eb000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f27b39eb000-7f27b39ec000 rw-p 00000000 00:00 0 
    7ffedd80a000-7ffedd82b000 rw-p 00000000 00:00 0                          [stack]
    7ffedd851000-7ffedd853000 r--p 00000000 00:00 0                          [vvar]
    7ffedd853000-7ffedd855000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest 0.4
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x00000000007f0018 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f72a3f207e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f72a3f2937a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f72a3f2d53c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f72a3ec9830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    007f0000-00811000 rw-p 00000000 00:00 0                                  [heap]
    7f729c000000-7f729c021000 rw-p 00000000 00:00 0 
    7f729c021000-7f72a0000000 ---p 00000000 00:00 0 
    7f72a3c93000-7f72a3ca9000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f72a3ca9000-7f72a3ea8000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f72a3ea8000-7f72a3ea9000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f72a3ea9000-7f72a4069000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f72a4069000-7f72a4269000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f72a4269000-7f72a426d000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f72a426d000-7f72a426f000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f72a426f000-7f72a4273000 rw-p 00000000 00:00 0 
    7f72a4273000-7f72a437b000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f72a437b000-7f72a457a000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f72a457a000-7f72a457b000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f72a457b000-7f72a457c000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f72a457c000-7f72a45a2000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f72a478f000-7f72a4792000 rw-p 00000000 00:00 0 
    7f72a479e000-7f72a47a1000 rw-p 00000000 00:00 0 
    7f72a47a1000-7f72a47a2000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f72a47a2000-7f72a47a3000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f72a47a3000-7f72a47a4000 rw-p 00000000 00:00 0 
    7ffdf348a000-7ffdf34ab000 rw-p 00000000 00:00 0                          [stack]
    7ffdf3564000-7ffdf3566000 r--p 00000000 00:00 0                          [vvar]
    7ffdf3566000-7ffdf3568000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest -0.4
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001ffb018 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f0258c757e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f0258c7e37a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f0258c8253c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f0258c1e830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01ffb000-0201c000 rw-p 00000000 00:00 0                                  [heap]
    7f0254000000-7f0254021000 rw-p 00000000 00:00 0 
    7f0254021000-7f0258000000 ---p 00000000 00:00 0 
    7f02589e8000-7f02589fe000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f02589fe000-7f0258bfd000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f0258bfd000-7f0258bfe000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f0258bfe000-7f0258dbe000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f0258dbe000-7f0258fbe000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f0258fbe000-7f0258fc2000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f0258fc2000-7f0258fc4000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f0258fc4000-7f0258fc8000 rw-p 00000000 00:00 0 
    7f0258fc8000-7f02590d0000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f02590d0000-7f02592cf000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f02592cf000-7f02592d0000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f02592d0000-7f02592d1000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f02592d1000-7f02592f7000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f02594e4000-7f02594e7000 rw-p 00000000 00:00 0 
    7f02594f3000-7f02594f6000 rw-p 00000000 00:00 0 
    7f02594f6000-7f02594f7000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f02594f7000-7f02594f8000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f02594f8000-7f02594f9000 rw-p 00000000 00:00 0 
    7fffcf9cb000-7fffcf9ec000 rw-p 00000000 00:00 0                          [stack]
    7fffcf9f6000-7fffcf9f8000 r--p 00000000 00:00 0                          [vvar]
    7fffcf9f8000-7fffcf9fa000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest -l
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000000c84018 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f09fe05f7e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f09fe06837a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f09fe06c53c]
    ./hhtest[0x4014d1]
    ./hhtest[0x400b27]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f09fe008830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    00c84000-00ca5000 rw-p 00000000 00:00 0                                  [heap]
    7f09f8000000-7f09f8021000 rw-p 00000000 00:00 0 
    7f09f8021000-7f09fc000000 ---p 00000000 00:00 0 
    7f09fddd2000-7f09fdde8000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f09fdde8000-7f09fdfe7000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f09fdfe7000-7f09fdfe8000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f09fdfe8000-7f09fe1a8000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f09fe1a8000-7f09fe3a8000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f09fe3a8000-7f09fe3ac000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f09fe3ac000-7f09fe3ae000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f09fe3ae000-7f09fe3b2000 rw-p 00000000 00:00 0 
    7f09fe3b2000-7f09fe4ba000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f09fe4ba000-7f09fe6b9000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f09fe6b9000-7f09fe6ba000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f09fe6ba000-7f09fe6bb000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f09fe6bb000-7f09fe6e1000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f09fe8ce000-7f09fe8d1000 rw-p 00000000 00:00 0 
    7f09fe8dd000-7f09fe8e0000 rw-p 00000000 00:00 0 
    7f09fe8e0000-7f09fe8e1000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f09fe8e1000-7f09fe8e2000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f09fe8e2000-7f09fe8e3000 rw-p 00000000 00:00 0 
    7ffd28c95000-7ffd28cb6000 rw-p 00000000 00:00 0                          [stack]
    7ffd28d67000-7ffd28d69000 r--p 00000000 00:00 0                          [vvar]
    7ffd28d69000-7ffd28d6b000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    Aborted
    hhtests complete. Check the results to see if they look OK.
    


### Marking

Heavy hitter marks: 0/20

Total score: (23/38) * 80.0 + 0 = 48/100

