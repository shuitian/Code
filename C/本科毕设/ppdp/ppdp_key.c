#include "ppdp.h"

int create_user_key(){
	element_random(key.g);
	element_printf("system parameter g = %B\n", key.g);
	
	//generate private key
	element_random(key.x);
	element_printf("private key = %B\n", key.x);
	
	//compute corresponding public key
	element_pow_zn(key.X, key.g, key.x);
	element_printf("public key = %B\n", key.X);

	write_into_file(key.g,"ppdp.g","w");
	write_into_file(key.x,"ppdp.x","w");
	write_into_file(key.X,"ppdp.X","w");
	
	return 1;
}

int create_trapdoor(){
	element_random(key.k);
	element_printf("random k = %B\n", key.k);
	
	element_pow_zn(key.K, key.g, key.k);
	element_printf("trapdoor K = %B\n", key.K);
	
	element_pow_zn(key.D, key.K, key.x);
	element_printf("trapdoor D = %B\n", key.D);

	write_into_file(key.k,"ppdp.k","w");
	write_into_file(key.K,"ppdp.K","w");
	write_into_file(key.D,"ppdp.D","w");
	
	return 1;
}

int create_verify_param(){
	
	element_random(key.u);
	element_printf("verify param u = %B\n", key.u);
	
	write_into_file(key.u,"ppdp.u","w");
	
	return 1;
}

int create_key(){	

	create_user_key();
	create_trapdoor();
	create_verify_param();
	return 1;
}
