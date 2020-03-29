## COMP0019 CW5 Grade Report
Graded at: 2020-03-29 20:35:22.446785
Graded for revision:  4bcccbc3406a523059628d8a3cca16f6a4978635

### Output


    CLEAN 
      COMPILE sh0019.c
    sh0019.c: In function ‘run_list’:
    sh0019.c:165:9: warning: variable ‘wifexit’ set but not used [-Wunused-but-set-variable]
         int wifexit;
             ^
    sh0019.c: In function ‘eval_line’:
    sh0019.c:418:25: warning: declaration of ‘temp’ shadows a global declaration [-Wshadow]
             struct command* temp = command_alloc();
                             ^
    sh0019.c:14:5: note: shadowed declaration is here
     int temp[2];
         ^
    sh0019.c: In function ‘run_list’:
    sh0019.c:169:5: warning: ignoring return value of ‘pipe’, declared with attribute warn_unused_result [-Wunused-result]
         pipe(pipefd);
         ^
    sh0019.c:183:21: warning: ignoring return value of ‘pipe’, declared with attribute warn_unused_result [-Wunused-result]
                         pipe(pipefd);
                         ^
    sh0019.c:206:25: warning: ignoring return value of ‘pipe’, declared with attribute warn_unused_result [-Wunused-result]
                             pipe(pipefd);
                             ^
    sh0019.c:384:24: warning: ‘wexitstatus’ may be used uninitialized in this function [-Wmaybe-uninitialized]
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
    Test ZOMBIE1: FAILED in 0.115 sec
        command  `sleep 0.05 & \n sleep 0.1 \n ps T`
        expected ``
        got      `2637 pts/0 Z+ 0:00 [sleep] <defunct>`
    Test ZOMBIE2: FAILED in 0.159 sec
        command  `sleep 0.05 & sleep 0.05 & sleep 0.05 & sleep 0.05 & \n sleep 0.07 \n sleep 0.07 \n ps T`
        expected ``
        got      `2647 pts/0 Z+ 0:00 [sleep] <defunct> 2648 pts/0 Z+ 0:00 [sleep] <defunct> 26...`
    Test REDIR1: FAILED in 0.004 sec
        command  `echo Start ; echo File > fREDIR1.txt`
        expected `Start File`
        got      `Start File cat: fREDIR1.txt: No such file or directory`
    Test REDIR2: FAILED in 0.003 sec
        command  `tr pq Fi < fREDIR2.txt ; echo Done`
        expected `File Done`
        got      ``
    Test REDIR3: FAILED in 0.005 sec
        command  `perl -e 'print STDERR 2289' 2> fREDIR3.txt ; grep '^[1-9]' fREDIR3.txt | wc -l ; rm -f fREDIR3.txt`
        expected `1`
        got      `2289`
    Test REDIR4: FAILED in 0.005 sec
        command  `perl -e 'print STDERR 2289; print STDOUT "X"' > fREDIR4a.txt 2> fREDIR4b.txt ; grep '^[1-9]' fREDIR4a.txt | wc -l ; grep '^[1-9]' fREDIR4b.txt | wc -l ; cmp -s fREDIR4a.txt fREDIR4b.txt || echo Different`
        expected `0 1 Different`
        got      `2289X`
    Test REDIR5: FAILED in 0.003 sec
        command  `tr hb HB < fREDIR5.txt | sort | ../sh0019 -q cmdREDIR5.sh`
        expected `Bye Hello First Good`
        got      ``
    Test REDIR6: FAILED in 0.003 sec
        command  `sort < fREDIR6a.txt > fREDIR6b.txt ; tail -n 2 fREDIR6b.txt ; rm -f fREDIR6a.txt fREDIR6b.txt`
        expected `Bye Hello`
        got      ``
    Test REDIR7: FAILED in 0.003 sec
        command  `echo > /tmp/directorydoesnotexist/foo`
        expected `No such file or directory`
        got      ``
    Test REDIR8: FAILED in 0.003 sec
        command  `echo > /tmp/directorydoesnotexist/foo && echo Unwanted`
        expected `No such file or directory`
        got      ``
    Test REDIR9: FAILED in 0.002 sec
        command  `echo > /tmp/directorydoesnotexist/foo || echo Wanted`
        expected `No such file or directory Wanted`
        got      ``
    Test REDIR10: FAILED in 0.003 sec
        command  `echo Hello < nonexistentREDIR10.txt`
        expected `No such file or directory`
        got      `Hello`
    Test REDIR11: FAILED in 0.003 sec
        command  `echo Hello < nonexistentREDIR11.txt && echo Unwanted`
        expected `No such file or directory`
        got      `Hello`
    Test REDIR12: FAILED in 0.003 sec
        command  `echo Hello < nonexistentREDIR12.txt || echo Wanted`
        expected `No such file or directory Wanted`
        got      `Hello`
    Test REDIR13: FAILED in 0.004 sec
        command  `cat unwanted.txt | cat < wanted.txt`
        expected `Wanted`
        got      `Unwanted`
    Test REDIR14: FAILED in 0.003 sec
        command  `cat < wanted.txt | cat > output.txt`
        expected `output.txt is Wanted`
        got      `output.txt is cat: output.txt: No such file or directory`
    Test REDIR15: FAILED in 0.003 sec
        command  `cat < xoqted.txt | tr xoq Wan | cat > output.txt`
        expected `output.txt is Wanted`
        got      `output.txt is cat: output.txt: No such file or directory`
    Test REDIR16: FAILED in 0.004 sec
        command  `echo Ignored | cat < lower.txt | tr A-Z a-z`
        expected `lower`
        got      `Ignored`
    Test INTR1: FAILED in 0.205 sec
        command  `echo a && sleep 0.2 && echo b`
        expected `a`
        got      `a b`
    Test INTR2: FAILED in 0.206 sec
        command  `echo start && sleep 0.2 && echo undesired  \n  echo end`
        expected `start end`
        got      `start undesired end`
    Test INTR3: FAILED in 0.504 sec
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
    Test CD1: FAILED in 0.012 sec
        command  `cd / ; pwd`
        expected `/`
        got      `/home/user/out`
    Test CD2: FAILED in 0.005 sec
        command  `cd / ; cd /usr ; pwd`
        expected `/usr`
        got      `/home/user/out`
    Test CD3: FAILED in 0.003 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null ; pwd`
        expected `/`
        got      `/home/user/grade/cd: 2: cd: can't cd to /doesnotexist`
    Test CD4: FAILED in 0.003 sec
        command  `cd / && pwd`
        expected `/`
        got      `/home/user/out`
    Test CD5: FAILED in 0.004 sec
        command  `echo go ; cd /doesnotexist 2> /dev/null > /dev/null && pwd`
        expected `go`
        got      `go /home/user/grade/cd: 2: cd: can't cd to /doesnotexist`
    Test CD6: FAILED in 0.003 sec
        command  `cd /doesnotexist 2> /dev/null > /dev/null || echo does not exist`
        expected `does not exist`
        got      `/home/user/grade/cd: 2: cd: can't cd to /doesnotexist`
    Test CD7: FAILED in 0.005 sec
        command  `cd /tmp && cd / && pwd`
        expected `/`
        got      `/home/user/out`
    Test CD8: FAILED in 0.004 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null > /dev/null ; pwd`
        expected `/`
        got      `/home/user/grade/cd: 2: cd: can't cd to /doesnotexist`
    Test ADVPIPE1: passed
    Test ADVBGCOND1: passed
    Test ADVBGCOND2: passed
    


### Marking

Total score: (63/100)

