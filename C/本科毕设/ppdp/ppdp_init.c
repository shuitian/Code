#include "ppdp.h"


void pbc_demo_pairing_init(pairing_t pairing) {
	char s[16384];
	FILE *fp = fopen("a.param", "r");
	if (!fp) pbc_die("error opening a.param");
	size_t count = fread(s, 1, 16384, fp);
	if (!count) pbc_die("input error");
	fclose(fp);
	
	if (pairing_init_set_buf(pairing, s, count)) pbc_die("pairing init failed");
}

void ppdp_init(){
	memset(&key,0,sizeof(key));
	memset(&verify,0,sizeof(verify));

	pbc_demo_pairing_init(pairing);
	//base
	element_init_G2(key.g, pairing);
	element_init_Zr(key.x, pairing);
	element_init_G2(key.X, pairing);
	
	//proxy
	element_init_Zr(key.k, pairing);
	element_init_G1(key.K, pairing);
	element_init_G1(key.D, pairing);
	
	//tag
	element_init_Zr(key.tmp, pairing);
	element_init_Zr(key.sum, pairing);
	
	//verify
	element_init_Zr(key.v, pairing);
	element_init_G1(key.u, pairing);
	element_init_G1(verify.h, pairing);
	element_init_G1(verify.sig, pairing);
	element_init_GT(verify.temp1, pairing);
	element_init_GT(verify.temp2, pairing);
	
}

void ppdp_clean(){
	//base
	element_clear(key.g);
	element_clear(key.x);
	element_clear(key.X);
	
	//proxy
	element_clear(key.k);
	element_clear(key.K);
	element_clear(key.D);
	
	//tag
	element_clear(key.tmp);
	element_clear(key.sum);
	
	//verify
	element_clear(key.v);
	element_clear(key.u);
	element_clear(verify.h);
	element_clear(verify.sig);
	element_clear(verify.temp1);
	element_clear(verify.temp2);
	
	pairing_clear(pairing);
}