
### Output:
Graded at: 2020-11-09 01:00:12.924639
```
rm -f ticker_prot.h ticker_prot_clnt.c ticker_prot_svc.c ticker_prot_xdr.c
rm -f ticker_prot_tbl.i ticker-client ticker-server score
rm -f *.core *.o *~
rm -f ticker_prot.h
rpcgen -C -h -o ticker_prot.h ticker_prot.x
cc -c -Wall -g client.c
rm -f ticker_prot_xdr.c
rpcgen -C -c -o ticker_prot_xdr.c ticker_prot.x
cc -c -Wall -g ticker_prot_xdr.c
rm -f ticker_prot_clnt.c
rpcgen -C -l -o ticker_prot_clnt.c ticker_prot.x
cc -c -Wall -g ticker_prot_clnt.c
cc -c -Wall -g minirpc.c
cc -Wall -g -o ticker-client client.o ticker_prot_xdr.o ticker_prot_clnt.o minirpc.o -L/usr/local/lib 
cc -c -Wall -g server.c
rm -f ticker_prot_svc.c
rpcgen -C -m -o ticker_prot_svc.c ticker_prot.x
cc -c -Wall -g ticker_prot_svc.c
cc -Wall -g -o ticker-server server.o ticker_prot_xdr.o ticker_prot_svc.o ticker_prot_clnt.o minirpc.o -L/usr/local/lib 
One server, one transaction (no points): passed
Two servers, one transaction (1 point): passed
Two servers, two transactions (1 point): passed
Two servers, ten concurrent transactions (2 points): passed
Five servers, continuous transactions (3 points): passed
One of two servers fail (1 point): passed
Three of six servers fail (2 points): passed
FINAL SCORE: 10/10
```