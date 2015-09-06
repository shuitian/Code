
#include <pbc/pbc.h>
#include <getopt.h>
#include <openssl/rsa.h>
#include <string.h>

#ifndef __PPDP_H__
#define __PPDP_H__


#define RSA_KEY_SIZE 1024
#define RSA_E RSA_F4
#define LENGTH 1000
#define PARAMLENGTH 312
static struct option longopts[] = {
	{"keygen", no_argument, NULL, 'k'}, //TODO optional argument for key location
	{"tag", no_argument, NULL, 't'},
	{"verify", no_argument, NULL, 'v'},
	{NULL, 0, NULL, 0}
};

typedef struct ppdpkey{
	element_t g;
	element_t x;
	element_t X;
	element_t k;
	element_t K;
	element_t D;
	element_t u;
	element_t tmp;
	element_t sum;
	element_t v;
}ppdp_key,*ppdp_key_ptr;

typedef struct ppdpverify{
	element_t h;
	element_t sig;
	element_t temp1;
	element_t temp2;
}ppdp_verify,*ppdp_verify_ptr;

//RSA *rsa_key;

pairing_t pairing;
ppdp_key key;
ppdp_verify verify;


unsigned char msg[LENGTH];
unsigned char msg1[LENGTH];
int i;
size_t rsa_flen;

unsigned char * ppdp_rsa_encrypt(unsigned char *);
unsigned char * ppdp_rsa_decrypt(unsigned char *);

#endif //__PPDP_H__