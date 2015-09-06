ppdp:ppdp.o ppdp_init.o ppdp_file.o ppdp_key.o ppdp_tag.o ppdp_verify.o
	gcc -o ppdp ppdp.o ppdp_init.o ppdp_file.o  ppdp_key.o ppdp_tag.o ppdp_verify.o -lgmp -lpbc -lssl -lcrypto

ppdp.o:ppdp.c ppdp.h
	gcc -c ppdp.c -I.

ppdp_init.o:ppdp_init.c ppdp.h
	gcc -c ppdp_init.c -l.
	
ppdp_file.o:ppdp_file.c ppdp.h
	gcc -c ppdp_file.c -l.
	
ppdp_key.o:ppdp_key.c ppdp.h
	gcc -c ppdp_key.c -l.
	
ppdp_tag.o:ppdp_tag.c ppdp.h
	gcc -c ppdp_tag.c -l.
	
ppdp_verify.o:ppdp_verify.c ppdp.h
	gcc -c ppdp_verify.c -l.
	
clean:
	-rm  -rf *.o *.X *.x *.u *.ph *.sig *.K *.g *.chal *.D *.k