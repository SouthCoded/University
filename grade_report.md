## COMP0019 CW5 Grade Report
Graded at: 2020-03-31 18:24:46.647192
Graded for revision:  5c3a36df9b5c6336abc1017f8011ea678728b7af

### Output


    CLEAN 
      COMPILE sh0019.c
    sh0019.c: In function ‘signal_handler’:
    sh0019.c:76:32: warning: unused parameter ‘a’ [-Wunused-parameter]
     static void signal_handler(int a){
                                    ^
    sh0019.c: In function ‘run_list’:
    sh0019.c:299:9: warning: variable ‘piper’ set but not used [-Wunused-but-set-variable]
         int piper = pipe(pipefd);
             ^
    sh0019.c:277:9: warning: variable ‘wifexit’ set but not used [-Wunused-but-set-variable]
         int wifexit;
             ^
    sh0019.c: In function ‘start_command’:
    sh0019.c:102:9: warning: ignoring return value of ‘chdir’, declared with attribute warn_unused_result [-Wunused-result]
             chdir((c->argv)[1]);
             ^
    sh0019.c: In function ‘run_list’:
    sh0019.c:566:24: warning: ‘wexitstatus’ may be used uninitialized in this function [-Wmaybe-uninitialized]
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
    Test INTR1: passed
    Test INTR2: passed
    Test INTR3: passed
    Test INTR4: passed
    Test INTR5: passed
    Test CD1: passed
    Test CD2: passed
    Test CD3: passed
    Test CD4: passed
    Test CD5: passed
    Test CD6: passed
    Test CD7: passed
    Test CD8: passed
    Test ADVPIPE1: passed
    Test ADVBGCOND1: passed
    Test ADVBGCOND2: passed
    


### Marking

Total score: (100/100)

