## COMP0019 CW2 Grade Report
Graded at: 2020-02-02 15:59:40.524593

Report for commit SHA: 06f74e47a309d5bcf09a964ca4d38c9efa767d9a

### Output


    CLEAN 
      COMPILE cs0019.c
    cs0019.c: In function ‘cs0019_printheavyhitterreport’:
    cs0019.c:532:14: warning: unknown conversion type character ‘)’ in format [-Wformat=]
           printf("HEAVY HITTER: %s:%d: %ld bytes (~%2.1f%)\n",array[x].file,array[x].line,array[x].size,percent*100);
                  ^
    cs0019.c:485:19: warning: unused variable ‘TM_traverse’ [-Wunused-variable]
       struct TM_node *TM_traverse = TM_head;   
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
    HEAVY HITTER: hhtest.c:169: 1639710720 bytes (~50.1%)
    HEAVY HITTER: hhtest.c:165: 811663360 bytes (~24.8%)
    
    ========================
    ./hhtest 1
    HEAVY HITTER: hhtest.c:13: 500773 bytes (~50.1%)
    HEAVY HITTER: hhtest.c:17: 249744 bytes (~25.0%)
    
    ========================
    ./hhtest 0.4
    
    ========================
    ./hhtest -0.4
    HEAVY HITTER: hhtest.c:169: 15835594752 bytes (~62.1%)
    HEAVY HITTER: hhtest.c:165: 6000738304 bytes (~23.5%)
    
    ========================
    ./hhtest -l
    HEAVY HITTER: hhtest.c:19064: 419379200 bytes (~53.2%)
    HEAVY HITTER: hhtest.c:13401: 367667200 bytes (~46.7%)
    hhtests complete. Check the results to see if they look OK.
    


### Marking

Heavy hitter marks: 20/20

Total score: (38/38) * 80.0 + 20 = 100/100

