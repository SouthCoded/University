## COMP0019 CW5 Grade Report
Graded at: 2020-03-29 20:44:20.612016
Graded for revision:  45abb40e630fe0a225d83712fba2ae739e171026

### Output


    CLEAN 
      COMPILE sh0019.c
    sh0019.c: In function ‘run_list’:
    sh0019.c:278:25: warning: declaration of ‘piper’ shadows a previous local [-Wshadow]
                         int piper = pipe(pipefd);
                             ^
    sh0019.c:265:9: note: shadowed declaration is here
         int piper = pipe(pipefd);
             ^
    sh0019.c:278:25: warning: unused variable ‘piper’ [-Wunused-variable]
                         int piper = pipe(pipefd);
                             ^
    sh0019.c:298:29: warning: declaration of ‘piper’ shadows a previous local [-Wshadow]
                             int piper = pipe(pipefd);
                                 ^
    sh0019.c:265:9: note: shadowed declaration is here
         int piper = pipe(pipefd);
             ^
    sh0019.c:298:29: warning: unused variable ‘piper’ [-Wunused-variable]
                             int piper = pipe(pipefd);
                                 ^
    sh0019.c:265:9: warning: variable ‘piper’ set but not used [-Wunused-but-set-variable]
         int piper = pipe(pipefd);
             ^
    sh0019.c:261:9: warning: variable ‘wifexit’ set but not used [-Wunused-but-set-variable]
         int wifexit;
             ^
    sh0019.c:498:24: warning: ‘wexitstatus’ may be used uninitialized in this function [-Wmaybe-uninitialized]
                     else if(wexitstatus != 0){
                            ^
      COMPILE helpers.c
      LINK sh0019 
    
    Test SIMPLE1: passed
    Test SIMPLE2: passed
    Test SIMPLE3: passed
    Test SIMPLE4: passed
    Test BG1: passed
    Test BG2: passed
    Test BG3: passed
    Test LIST1: passed
    Test LIST2: passed
    Test LIST3: passed
    Test LIST4: passed
    Test LIST5: passed
    Test LIST6: passed
    Test LIST7: passed
    Test LIST8: passed
    Test COND1: passed
    Test COND2: passed
    Test COND3: passed
    Test COND4: passed
    Test COND5: passed
    Test COND6: passed
    Test COND7: passed
    Test COND8: passed
    Test COND9: passed
    Test COND10: passed
    Test COND11: passed
    Test PIPE1: passed
    Test PIPE2: passed
    Test PIPE3: passed
    Test PIPE4: passed
    Test PIPE5: passed
    Test PIPE6: passed
    Test PIPE7: passed
    Test PIPE8: passed
    Test PIPE9: passed
    Test PIPE10: passed
    Test PIPE11: passed
    Test PIPE12: passed
    Test PIPE13: passed
    Test PIPE14: passed
    Test PIPE15: passed
    Test PIPE16: passed
    Test PIPE17: passed
    Test PIPE18: passed
    Test PIPE19: passed
    Test PIPE20: passed
    Test PIPE21: passed
    Test PIPE22: passed
    Test PIPE23: passed
    Test ZOMBIE1: passed
    Test ZOMBIE2: passed
    Test REDIR1: passed
    Test REDIR2: passed
    Test REDIR3: passed
    Test REDIR4: passed
    Test REDIR5: passed
    Test REDIR6: passed
    Test REDIR7: passed
    Test REDIR8: passed
    Test REDIR9: passed
    Test REDIR10: passed
    Test REDIR11: passed
    Test REDIR12: passed
    Test REDIR13: passed
    Test REDIR14: passed
    Test REDIR15: passed
    Test REDIR16: passed
    Test INTR1: FAILED in 0.205 sec
        command  `echo a && sleep 0.2 && echo b`
        expected `a`
        got      `a b`
    Test INTR2: FAILED in 0.206 sec
        command  `echo start && sleep 0.2 && echo undesired  \n  echo end`
        expected `start end`
        got      `start undesired end`
    Test INTR3: FAILED in 0.507 sec
        command  `sleep 0.3 && echo yes & sleep 0.2 && echo no`
        expected `yes`
        got      `no yes`
    Test INTR4: FAILED in 1.004 sec
        command  `sleep 1`
        should have completed in 0.150 sec
    Test INTR5: FAILED in 1.006 sec
        command  `../sh0019 -q cmdINTR5.sh`
        expected ``
        got      `undesired`
        should have completed in 0.150 sec
    Test CD1: FAILED in 0.028 sec
        command  `cd / ; pwd`
        expected `/`
        got      `/home/user/out`
    Test CD2: FAILED in 0.004 sec
        command  `cd / ; cd /usr ; pwd`
        expected `/usr`
        got      `/home/user/out`
    Test CD3: FAILED in 0.005 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null ; pwd`
        expected `/`
        got      `/home/user/out`
    Test CD4: FAILED in 0.004 sec
        command  `cd / && pwd`
        expected `/`
        got      `/home/user/out`
    Test CD5: passed
    Test CD6: passed
    Test CD7: FAILED in 0.005 sec
        command  `cd /tmp && cd / && pwd`
        expected `/`
        got      `/home/user/out`
    Test CD8: FAILED in 0.005 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null > /dev/null ; pwd`
        expected `/`
        got      `/home/user/out`
    Test ADVPIPE1: passed
    Test ADVBGCOND1: passed
    Test ADVBGCOND2: passed
    


### Marking

Total score: (87/100)

