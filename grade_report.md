## COMP0019 CW5 Grade Report
Graded at: 2020-03-21 15:39:20.610201
Graded for revision:  d6b58b1d77a5c4003da18ea93928cfb00e39d804

### Output


    CLEAN 
      COMPILE sh0019.c
      COMPILE helpers.c
      LINK sh0019 
    
    Test SIMPLE1: FAILED in 0.001 sec
        command  `echo Hooray`
        expected `Hooray`
        got      `start_command not done yet run_command not done yet`
    Test SIMPLE2: FAILED in 0.002 sec
        command  `echo Double Hooray`
        expected `Double Hooray`
        got      `start_command not done yet run_command not done yet`
    Test SIMPLE3: FAILED in 0.002 sec
        command  `cat f3.txt`
        expected `Triple Hooray`
        got      `start_command not done yet run_command not done yet`
    Test SIMPLE4: FAILED in 0.001 sec
        command  `echo Line 1 \n echo Line 2 \n echo Line 3`
        expected `Line 1 Line 2 Line 3`
        got      `start_command not done yet run_command not done yet start_command not done y...`
    Test BG1: FAILED in 0.002 sec
        command  `cp fBG1a.txt fBG1b.txt &`
        expected `Copied`
        got      `start_command not done yet run_command not done yet Original`
    Test BG2: FAILED in 0.002 sec
        command  `sh -c "sleep 0.2; test -r fBG2b.txt && rm -f fBG2a.txt" &`
        expected `Still here`
        got      `start_command not done yet run_command not done yet Still here`
    Test BG3: FAILED in 0.001 sec
        command  `sleep 2 &`
        expected `1`
        got      `start_command not done yet run_command not done yet 0`
    Test LIST1: FAILED in 0.001 sec
        command  `echo Semi ;`
        expected `Semi`
        got      `start_command not done yet run_command not done yet`
    Test LIST2: FAILED in 0.001 sec
        command  `echo Semi ; echo Colon`
        expected `Semi Colon`
        got      `start_command not done yet run_command not done yet`
    Test LIST3: FAILED in 0.001 sec
        command  `echo Semi ; echo Colon ; echo Rocks`
        expected `Semi Colon Rocks`
        got      `start_command not done yet run_command not done yet`
    Test LIST4: FAILED in 0.001 sec
        command  `echo Hello ;   echo There ; echo Who ; echo Are ; echo You ; echo ?`
        expected `Hello There Who Are You ?`
        got      `start_command not done yet run_command not done yet`
    Test LIST5: FAILED in 0.001 sec
        command  `rm -f fLIST5.txt ; echo Removed`
        expected `Removed`
        got      `start_command not done yet run_command not done yet`
    Test LIST6: FAILED in 0.001 sec
        command  `../sh0019 -q cmdLIST6.sh &`
        expected `Hello 1`
        got      `start_command not done yet run_command not done yet 0`
    Test LIST7: FAILED in 0.001 sec
        command  `../sh0019 -q cmdLIST7.sh`
        expected `Hello Bye 1`
        got      `start_command not done yet run_command not done yet 0`
    Test LIST8: FAILED in 0.001 sec
        command  `sh -c "sleep 0.2; echo Second" & sh -c "sleep 0.15; echo First" & sleep 0.3`
        expected `First Second`
        got      `start_command not done yet run_command not done yet`
    Test COND1: FAILED in 0.001 sec
        command  `true && echo True`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test COND2: FAILED in 0.001 sec
        command  `echo True || echo False`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test COND3: FAILED in 0.001 sec
        command  `grep -cv NotThere ../sh0019.c && echo Wanted`
        expected `189 Wanted`
        got      `start_command not done yet run_command not done yet`
    Test COND4: FAILED in 0.001 sec
        command  `grep -c NotThere ../sh0019.c && echo Unwanted`
        expected `0`
        got      `start_command not done yet run_command not done yet`
    Test COND5: FAILED in 0.001 sec
        command  `false || echo True`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test COND6: FAILED in 0.001 sec
        command  `true && false || true && echo Good`
        expected `Good`
        got      `start_command not done yet run_command not done yet`
    Test COND7: FAILED in 0.001 sec
        command  `echo Start && false || false && echo Bad`
        expected `Start`
        got      `start_command not done yet run_command not done yet`
    Test COND8: FAILED in 0.001 sec
        command  `sleep 0.2 && echo Second & sleep 0.1 && echo First`
        expected `First Second`
        got      `start_command not done yet run_command not done yet`
    Test COND9: FAILED in 0.001 sec
        command  `echo Start && false || false && false || echo End`
        expected `Start End`
        got      `start_command not done yet run_command not done yet`
    Test COND10: FAILED in 0.001 sec
        command  `false && echo no && echo no && echo no && echo no || echo yes`
        expected `yes`
        got      `start_command not done yet run_command not done yet`
    Test COND11: FAILED in 0.001 sec
        command  `true || echo no || echo no || echo no || echo no && echo yes`
        expected `yes`
        got      `start_command not done yet run_command not done yet`
    Test PIPE1: FAILED in 0.001 sec
        command  `echo Pipe | wc -c`
        expected `5`
        got      `start_command not done yet run_command not done yet`
    Test PIPE2: FAILED in 0.001 sec
        command  `echo Good | grep -n G`
        expected `1:Good`
        got      `start_command not done yet run_command not done yet`
    Test PIPE3: FAILED in 0.001 sec
        command  `echo Bad | grep -c G`
        expected `0`
        got      `start_command not done yet run_command not done yet`
    Test PIPE4: FAILED in 0.001 sec
        command  `echo Line | cat | wc -l`
        expected `1`
        got      `start_command not done yet run_command not done yet`
    Test PIPE5: FAILED in 0.001 sec
        command  `../sh0019 -q cmdPIPE5.sh; ps | grep sleep | grep -v grep | head -n 1 | wc -l`
        expected `Hello Bye 1`
        got      `start_command not done yet run_command not done yet`
    Test PIPE6: FAILED in 0.001 sec
        command  `echo GoHangASalamiImALasagnaHog | rev | rev | rev`
        expected `goHangasaLAmIimalaSAgnaHoG`
        got      `start_command not done yet run_command not done yet`
    Test PIPE7: FAILED in 0.001 sec
        command  `rev fPIPE7.txt | rev`
        expected `goHangasaLAmIimalaSAgnaHoG`
        got      `start_command not done yet run_command not done yet`
    Test PIPE8: FAILED in 0.001 sec
        command  `cat fPIPE8.txt | tr [A-Z] [a-z] | /usr/bin/md5sum | tr -d -`
        expected `8e21d03f7955611616bcd2337fe9eac1`
        got      `start_command not done yet run_command not done yet`
    Test PIPE9: FAILED in 0.002 sec
        command  `rev fPIPE9.txt | /usr/bin/md5sum | tr [a-z] [A-Z] | tr -d -`
        expected `502B109B37EC769342948826736FA063`
        got      `start_command not done yet run_command not done yet`
    Test PIPE10: FAILED in 0.002 sec
        command  `sleep 2 & sleep 0.2; ps T | grep sleep | grep -v grep | head -n 1 | wc -l`
        expected `1`
        got      `start_command not done yet run_command not done yet`
    Test PIPE11: FAILED in 0.002 sec
        command  `echo Sedi | tr d m ; echo Calan | tr a o`
        expected `Semi Colon`
        got      `start_command not done yet run_command not done yet`
    Test PIPE12: FAILED in 0.002 sec
        command  `echo Ignored | echo Desired`
        expected `Desired`
        got      `start_command not done yet run_command not done yet`
    Test PIPE13: FAILED in 0.002 sec
        command  `../sh0019 -q cmdPIPE13.sh &`
        expected `Hello 1`
        got      `start_command not done yet run_command not done yet start_command not done y...`
    Test PIPE14: FAILED in 0.002 sec
        command  `true | true && echo True`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test PIPE15: FAILED in 0.002 sec
        command  `true | echo True || echo False`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test PIPE16: FAILED in 0.002 sec
        command  `false | echo True || echo False`
        expected `True`
        got      `start_command not done yet run_command not done yet`
    Test PIPE17: FAILED in 0.002 sec
        command  `echo Hello | grep -q X || echo NoXs`
        expected `NoXs`
        got      `start_command not done yet run_command not done yet`
    Test PIPE18: FAILED in 0.002 sec
        command  `echo Yes | grep -q Y && echo Ys`
        expected `Ys`
        got      `start_command not done yet run_command not done yet`
    Test PIPE19: FAILED in 0.002 sec
        command  `echo Hello | grep -q X || echo poqs | tr pq NX`
        expected `NoXs`
        got      `start_command not done yet run_command not done yet`
    Test PIPE20: FAILED in 0.002 sec
        command  `echo Yes | grep -q Y && echo fs | tr f Y`
        expected `Ys`
        got      `start_command not done yet run_command not done yet`
    Test PIPE21: FAILED in 0.002 sec
        command  `false && echo vnexpected | tr v u ; echo expected`
        expected `expected`
        got      `start_command not done yet run_command not done yet`
    Test PIPE22: FAILED in 0.002 sec
        command  `false && echo unexpected && echo vnexpected | tr v u ; echo expected`
        expected `expected`
        got      `start_command not done yet run_command not done yet`
    Test PIPE23: FAILED in 0.002 sec
        command  `sleep 0.2 | wc -c | sed s/0/Second/ & sleep 0.1 | wc -c | sed s/0/First/`
        expected `First Second`
        got      `start_command not done yet run_command not done yet`
    Test ZOMBIE1: passed
    Test ZOMBIE2: passed
    Test REDIR1: FAILED in 0.002 sec
        command  `echo Start ; echo File > fREDIR1.txt`
        expected `Start File`
        got      `start_command not done yet run_command not done yet cat: fREDIR1.txt: No suc...`
    Test REDIR2: FAILED in 0.002 sec
        command  `tr pq Fi < fREDIR2.txt ; echo Done`
        expected `File Done`
        got      `start_command not done yet run_command not done yet`
    Test REDIR3: FAILED in 0.002 sec
        command  `perl -e 'print STDERR 2699' 2> fREDIR3.txt ; grep '^[1-9]' fREDIR3.txt | wc -l ; rm -f fREDIR3.txt`
        expected `1`
        got      `start_command not done yet run_command not done yet`
    Test REDIR4: FAILED in 0.002 sec
        command  `perl -e 'print STDERR 2699; print STDOUT "X"' > fREDIR4a.txt 2> fREDIR4b.txt ; grep '^[1-9]' fREDIR4a.txt | wc -l ; grep '^[1-9]' fREDIR4b.txt | wc -l ; cmp -s fREDIR4a.txt fREDIR4b.txt || echo Different`
        expected `0 1 Different`
        got      `start_command not done yet run_command not done yet`
    Test REDIR5: FAILED in 0.002 sec
        command  `tr hb HB < fREDIR5.txt | sort | ../sh0019 -q cmdREDIR5.sh`
        expected `Bye Hello First Good`
        got      `start_command not done yet run_command not done yet`
    Test REDIR6: FAILED in 0.002 sec
        command  `sort < fREDIR6a.txt > fREDIR6b.txt ; tail -n 2 fREDIR6b.txt ; rm -f fREDIR6a.txt fREDIR6b.txt`
        expected `Bye Hello`
        got      `start_command not done yet run_command not done yet`
    Test REDIR7: FAILED in 0.002 sec
        command  `echo > /tmp/directorydoesnotexist/foo`
        expected `No such file or directory`
        got      `start_command not done yet run_command not done yet`
    Test REDIR8: FAILED in 0.002 sec
        command  `echo > /tmp/directorydoesnotexist/foo && echo Unwanted`
        expected `No such file or directory`
        got      `start_command not done yet run_command not done yet`
    Test REDIR9: FAILED in 0.002 sec
        command  `echo > /tmp/directorydoesnotexist/foo || echo Wanted`
        expected `No such file or directory Wanted`
        got      `start_command not done yet run_command not done yet`
    Test REDIR10: FAILED in 0.002 sec
        command  `echo Hello < nonexistentREDIR10.txt`
        expected `No such file or directory`
        got      `start_command not done yet run_command not done yet`
    Test REDIR11: FAILED in 0.002 sec
        command  `echo Hello < nonexistentREDIR11.txt && echo Unwanted`
        expected `No such file or directory`
        got      `start_command not done yet run_command not done yet`
    Test REDIR12: FAILED in 0.001 sec
        command  `echo Hello < nonexistentREDIR12.txt || echo Wanted`
        expected `No such file or directory Wanted`
        got      `start_command not done yet run_command not done yet`
    Test REDIR13: FAILED in 0.002 sec
        command  `cat unwanted.txt | cat < wanted.txt`
        expected `Wanted`
        got      `start_command not done yet run_command not done yet`
    Test REDIR14: FAILED in 0.001 sec
        command  `cat < wanted.txt | cat > output.txt`
        expected `output.txt is Wanted`
        got      `start_command not done yet run_command not done yet output.txt is cat: outpu...`
    Test REDIR15: FAILED in 0.002 sec
        command  `cat < xoqted.txt | tr xoq Wan | cat > output.txt`
        expected `output.txt is Wanted`
        got      `start_command not done yet run_command not done yet output.txt is cat: outpu...`
    Test REDIR16: FAILED in 0.002 sec
        command  `echo Ignored | cat < lower.txt | tr A-Z a-z`
        expected `lower`
        got      `start_command not done yet run_command not done yet`
    Test INTR1: FAILED in 0.002 sec
        command  `echo a && sleep 0.2 && echo b`
        expected `a`
        got      `start_command not done yet run_command not done yet`
    Test INTR2: FAILED in 0.002 sec
        command  `echo start && sleep 0.2 && echo undesired  \n  echo end`
        expected `start end`
        got      `start_command not done yet run_command not done yet start_command not done y...`
    Test INTR3: FAILED in 0.002 sec
        command  `sleep 0.3 && echo yes & sleep 0.2 && echo no`
        expected `yes`
        got      `start_command not done yet run_command not done yet`
    Test INTR4: FAILED in 0.002 sec
        command  `sleep 1`
        expected ``
        got      `start_command not done yet run_command not done yet`
    Test INTR5: FAILED in 0.002 sec
        command  `../sh0019 -q cmdINTR5.sh`
        expected ``
        got      `start_command not done yet run_command not done yet`
    Test CD1: FAILED in 0.001 sec
        command  `cd / ; pwd`
        expected `/`
        got      `start_command not done yet run_command not done yet`
    Test CD2: FAILED in 0.001 sec
        command  `cd / ; cd /usr ; pwd`
        expected `/usr`
        got      `start_command not done yet run_command not done yet`
    Test CD3: FAILED in 0.001 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null ; pwd`
        expected `/`
        got      `start_command not done yet run_command not done yet`
    Test CD4: FAILED in 0.001 sec
        command  `cd / && pwd`
        expected `/`
        got      `start_command not done yet run_command not done yet`
    Test CD5: FAILED in 0.001 sec
        command  `echo go ; cd /doesnotexist 2> /dev/null > /dev/null && pwd`
        expected `go`
        got      `start_command not done yet run_command not done yet`
    Test CD6: FAILED in 0.001 sec
        command  `cd /doesnotexist 2> /dev/null > /dev/null || echo does not exist`
        expected `does not exist`
        got      `start_command not done yet run_command not done yet`
    Test CD7: FAILED in 0.001 sec
        command  `cd /tmp && cd / && pwd`
        expected `/`
        got      `start_command not done yet run_command not done yet`
    Test CD8: FAILED in 0.001 sec
        command  `cd / ; cd /doesnotexist 2> /dev/null > /dev/null ; pwd`
        expected `/`
        got      `start_command not done yet run_command not done yet`
    Test ADVPIPE1: FAILED in 0.001 sec
        command  `yes | head -n 5`
        expected `y y y y y`
        got      `start_command not done yet run_command not done yet`
    Test ADVBGCOND1: FAILED in 0.001 sec
        command  `sleep 0.2 && echo second & echo first`
        expected `first second`
        got      `start_command not done yet run_command not done yet`
    Test ADVBGCOND2: FAILED in 0.001 sec
        command  `echo first && sleep 0.1 && echo third & sleep 0.05 ; echo second ; sleep 0.1 ; echo fourth`
        expected `first second third fourth`
        got      `start_command not done yet run_command not done yet`
    


### Marking

Total score: (2/100)

