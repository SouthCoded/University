## COMP0019 CW2 Grade Report
Graded at: 2020-01-25 18:03:15.512067

Report for commit SHA: fe03b918b24148597172418dfb88ae5161a35c39

### Output


    CLEAN 
      COMPILE cs0019.c
    cs0019.c:17:18: warning: integer constant is too large for its type
     char* heap_min = 0xfffffffffffffffff;
                      ^
    cs0019.c:17:18: warning: initialization makes pointer from integer without a cast [-Wint-conversion]
    cs0019.c: In function ‘cs0019_malloc’:
    cs0019.c:64:16: warning: assignment from incompatible pointer type [-Wincompatible-pointer-types]
           heap_min = base + metadata_size;
                    ^
    cs0019.c:66:23: warning: comparison of distinct pointer types lacks a cast
         else if (heap_min > base + metadata_size){
                           ^
    cs0019.c:67:16: warning: assignment from incompatible pointer type [-Wincompatible-pointer-types]
           heap_min = base + metadata_size;
                    ^
    cs0019.c:71:16: warning: assignment from incompatible pointer type [-Wincompatible-pointer-types]
           heap_max = base + metadata_size + sz;
                    ^
    cs0019.c:73:23: warning: comparison of distinct pointer types lacks a cast
         else if (heap_max < base + metadata_size + sz){
                           ^
    cs0019.c:74:16: warning: assignment from incompatible pointer type [-Wincompatible-pointer-types]
           heap_max = base + metadata_size + sz;
                    ^
    cs0019.c: In function ‘cs0019_free’:
    cs0019.c:126:12: warning: comparison of distinct pointer types lacks a cast
         if(ptr < heap_min || ptr > heap_max){
                ^
    cs0019.c:126:30: warning: comparison of distinct pointer types lacks a cast
         if(ptr < heap_min || ptr > heap_max){
                                  ^
    cs0019.c: In function ‘cs0019_realloc’:
    cs0019.c:181:33: warning: initialization from incompatible pointer type [-Wincompatible-pointer-types]
         struct metadata *temp_ptr = (char* ) ptr;
                                     ^
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
    test031 FAIL: Missing output starting on line 0
      test031.c:33: Expected `OK`
    test032 FAIL: Missing output starting on line 0
      test032.c:39: Expected `EXPECTED LEAK: ??{0x\w*}=pointer?? with size ??{\d+}=size??`
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
    22 of 38 tests passed
    make: 'hhtest' is up to date.
    ./hhtest 0
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001eca050 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f3d4396e7e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f3d4397737a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f3d4397b53c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f3d43917830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01eca000-01eeb000 rw-p 00000000 00:00 0                                  [heap]
    7f3d3c000000-7f3d3c021000 rw-p 00000000 00:00 0 
    7f3d3c021000-7f3d40000000 ---p 00000000 00:00 0 
    7f3d436e1000-7f3d436f7000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f3d436f7000-7f3d438f6000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f3d438f6000-7f3d438f7000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f3d438f7000-7f3d43ab7000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f3d43ab7000-7f3d43cb7000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f3d43cb7000-7f3d43cbb000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f3d43cbb000-7f3d43cbd000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f3d43cbd000-7f3d43cc1000 rw-p 00000000 00:00 0 
    7f3d43cc1000-7f3d43dc9000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f3d43dc9000-7f3d43fc8000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f3d43fc8000-7f3d43fc9000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f3d43fc9000-7f3d43fca000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f3d43fca000-7f3d43ff0000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f3d441dd000-7f3d441e0000 rw-p 00000000 00:00 0 
    7f3d441ec000-7f3d441ef000 rw-p 00000000 00:00 0 
    7f3d441ef000-7f3d441f0000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f3d441f0000-7f3d441f1000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f3d441f1000-7f3d441f2000 rw-p 00000000 00:00 0 
    7fff38bd4000-7fff38bf5000 rw-p 00000000 00:00 0                          [stack]
    7fff38bf7000-7fff38bf9000 r--p 00000000 00:00 0                          [vvar]
    7fff38bf9000-7fff38bfb000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    Aborted
    
    ========================
    ./hhtest 1
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x00000000013fa050 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f52a62c67e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f52a62cf37a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f52a62d353c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f52a626f830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    013fa000-0141b000 rw-p 00000000 00:00 0                                  [heap]
    7f52a0000000-7f52a0021000 rw-p 00000000 00:00 0 
    7f52a0021000-7f52a4000000 ---p 00000000 00:00 0 
    7f52a6039000-7f52a604f000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f52a604f000-7f52a624e000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f52a624e000-7f52a624f000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f52a624f000-7f52a640f000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f52a640f000-7f52a660f000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f52a660f000-7f52a6613000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f52a6613000-7f52a6615000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f52a6615000-7f52a6619000 rw-p 00000000 00:00 0 
    7f52a6619000-7f52a6721000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f52a6721000-7f52a6920000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f52a6920000-7f52a6921000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f52a6921000-7f52a6922000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f52a6922000-7f52a6948000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f52a6b35000-7f52a6b38000 rw-p 00000000 00:00 0 
    7f52a6b44000-7f52a6b47000 rw-p 00000000 00:00 0 
    7f52a6b47000-7f52a6b48000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f52a6b48000-7f52a6b49000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f52a6b49000-7f52a6b4a000 rw-p 00000000 00:00 0 
    7ffc3995f000-7ffc39980000 rw-p 00000000 00:00 0                          [stack]
    7ffc3999c000-7ffc3999e000 r--p 00000000 00:00 0                          [vvar]
    7ffc3999e000-7ffc399a0000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest 0.4
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001f7f050 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f5a1c9557e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f5a1c95e37a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f5a1c96253c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f5a1c8fe830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01f7f000-01fa0000 rw-p 00000000 00:00 0                                  [heap]
    7f5a18000000-7f5a18021000 rw-p 00000000 00:00 0 
    7f5a18021000-7f5a1c000000 ---p 00000000 00:00 0 
    7f5a1c6c8000-7f5a1c6de000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f5a1c6de000-7f5a1c8dd000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f5a1c8dd000-7f5a1c8de000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f5a1c8de000-7f5a1ca9e000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f5a1ca9e000-7f5a1cc9e000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f5a1cc9e000-7f5a1cca2000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f5a1cca2000-7f5a1cca4000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f5a1cca4000-7f5a1cca8000 rw-p 00000000 00:00 0 
    7f5a1cca8000-7f5a1cdb0000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f5a1cdb0000-7f5a1cfaf000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f5a1cfaf000-7f5a1cfb0000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f5a1cfb0000-7f5a1cfb1000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f5a1cfb1000-7f5a1cfd7000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f5a1d1c4000-7f5a1d1c7000 rw-p 00000000 00:00 0 
    7f5a1d1d3000-7f5a1d1d6000 rw-p 00000000 00:00 0 
    7f5a1d1d6000-7f5a1d1d7000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f5a1d1d7000-7f5a1d1d8000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f5a1d1d8000-7f5a1d1d9000 rw-p 00000000 00:00 0 
    7ffe9b5cd000-7ffe9b5ee000 rw-p 00000000 00:00 0                          [stack]
    7ffe9b5fc000-7ffe9b5fe000 r--p 00000000 00:00 0                          [vvar]
    7ffe9b5fe000-7ffe9b600000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    
    ========================
    ./hhtest -0.4
    *** Error in `./hhtest': free(): invalid pointer: 0x0000000001b37050 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f1546c607e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f1546c6937a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f1546c6d53c]
    ./hhtest[0x40164a]
    ./hhtest[0x400ab1]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f1546c09830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    01b37000-01b58000 rw-p 00000000 00:00 0                                  [heap]
    7f1540000000-7f1540021000 rw-p 00000000 00:00 0 
    7f1540021000-7f1544000000 ---p 00000000 00:00 0 
    7f15469d3000-7f15469e9000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f15469e9000-7f1546be8000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f1546be8000-7f1546be9000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f1546be9000-7f1546da9000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f1546da9000-7f1546fa9000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f1546fa9000-7f1546fad000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f1546fad000-7f1546faf000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f1546faf000-7f1546fb3000 rw-p 00000000 00:00 0 
    7f1546fb3000-7f15470bb000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f15470bb000-7f15472ba000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f15472ba000-7f15472bb000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f15472bb000-7f15472bc000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f15472bc000-7f15472e2000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f15474cf000-7f15474d2000 rw-p 00000000 00:00 0 
    7f15474de000-7f15474e1000 rw-p 00000000 00:00 0 
    7f15474e1000-7f15474e2000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f15474e2000-7f15474e3000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f15474e3000-7f15474e4000 rw-p 00000000 00:00 0 
    7ffe6951d000-7ffe6953e000 rw-p 00000000 00:00 0                          [stack]
    7ffe695e0000-7ffe695e2000 r--p 00000000 00:00 0                          [vvar]
    7ffe695e2000-7ffe695e4000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    Aborted
    
    ========================
    ./hhtest -l
    Aborted
    *** Error in `./hhtest': free(): invalid pointer: 0x00000000008e4050 ***
    ======= Backtrace: =========
    /lib/x86_64-linux-gnu/libc.so.6(+0x777e5)[0x7f2bf83007e5]
    /lib/x86_64-linux-gnu/libc.so.6(+0x8037a)[0x7f2bf830937a]
    /lib/x86_64-linux-gnu/libc.so.6(cfree+0x4c)[0x7f2bf830d53c]
    ./hhtest[0x4014d1]
    ./hhtest[0x400b27]
    /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0)[0x7f2bf82a9830]
    ./hhtest[0x400b89]
    ======= Memory map: ========
    00400000-00403000 r-xp 00000000 08:01 422594                             /home/user/hhtest
    00602000-00603000 r--p 00002000 08:01 422594                             /home/user/hhtest
    00603000-00604000 rw-p 00003000 08:01 422594                             /home/user/hhtest
    008e4000-00905000 rw-p 00000000 00:00 0                                  [heap]
    7f2bf4000000-7f2bf4021000 rw-p 00000000 00:00 0 
    7f2bf4021000-7f2bf8000000 ---p 00000000 00:00 0 
    7f2bf8073000-7f2bf8089000 r-xp 00000000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f2bf8089000-7f2bf8288000 ---p 00016000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f2bf8288000-7f2bf8289000 rw-p 00015000 08:01 536                        /lib/x86_64-linux-gnu/libgcc_s.so.1
    7f2bf8289000-7f2bf8449000 r-xp 00000000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f2bf8449000-7f2bf8649000 ---p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f2bf8649000-7f2bf864d000 r--p 001c0000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f2bf864d000-7f2bf864f000 rw-p 001c4000 08:01 510                        /lib/x86_64-linux-gnu/libc-2.23.so
    7f2bf864f000-7f2bf8653000 rw-p 00000000 00:00 0 
    7f2bf8653000-7f2bf875b000 r-xp 00000000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f2bf875b000-7f2bf895a000 ---p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f2bf895a000-7f2bf895b000 r--p 00107000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f2bf895b000-7f2bf895c000 rw-p 00108000 08:01 551                        /lib/x86_64-linux-gnu/libm-2.23.so
    7f2bf895c000-7f2bf8982000 r-xp 00000000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f2bf8b6f000-7f2bf8b72000 rw-p 00000000 00:00 0 
    7f2bf8b7e000-7f2bf8b81000 rw-p 00000000 00:00 0 
    7f2bf8b81000-7f2bf8b82000 r--p 00025000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f2bf8b82000-7f2bf8b83000 rw-p 00026000 08:01 486                        /lib/x86_64-linux-gnu/ld-2.23.so
    7f2bf8b83000-7f2bf8b84000 rw-p 00000000 00:00 0 
    7ffcb1c14000-7ffcb1c35000 rw-p 00000000 00:00 0                          [stack]
    7ffcb1df8000-7ffcb1dfa000 r--p 00000000 00:00 0                          [vvar]
    7ffcb1dfa000-7ffcb1dfc000 r-xp 00000000 00:00 0                          [vdso]
    ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
    timeout: the monitored command dumped core
    hhtests complete. Check the results to see if they look OK.
    


### Marking

Heavy hitter marks: 0/20

Total score: (22/38) * 80.0 + 0 = 46/100

