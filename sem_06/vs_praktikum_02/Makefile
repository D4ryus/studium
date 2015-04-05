CC = gcc

OBJECTS_CLIENT = rdict_xdr.o rdict_cif.o rdict_clnt.o rdict.o
OBJECTS_SERVER = rdict_xdr.o rdict_sif.o rdict_svc.o  rdict_srp.o

%.o : %.c
	$(CC) -c -o $@ $^

gen : rdict.x
	rpcgen rdict.x

rdictd : $(OBJECTS_SERVER)
	$(CC) -o $@ $^

rdict : $(OBJECTS_CLIENT)
	$(CC) -o $@ $^

run_rdictd : rdictd
	./$<

run_rdict : rdict
	./$<

clean :
	rm *.o
