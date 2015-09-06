#include "ppdp.h"

int read_verify_param(){
	read_from_file(key.g,"ppdp.g");
	read_from_file(key.X,"ppdp.X");
	read_from_file(key.K,"ppdp.K");
	read_from_file(key.D,"ppdp.D");
	read_from_file(key.u,"ppdp.u");
	return 1;
}

int check_proxy(){
	element_pairing(verify.temp1, key.K, key.X);
	element_printf("f( K , X ) = %B\n", verify.temp1);

	element_pairing(verify.temp2, key.D , key.g);
	element_printf("f( D , g ) = %B\n", verify.temp2);

	if (!element_cmp(verify.temp1, verify.temp2)) {
		printf("proxy verifies\n");
		return 1;
	} else {
		printf("*BUG* proxy does not verify *BUG*\n");
		return 0;
	}
}

int check_file(unsigned char *path){
	size_t len;
	
	clear_file("ppdp.chal");
	read_file_tag(path);
	
	read_from_file(verify.sig,"ppdp.sig");
	read_from_file(verify.h,"ppdp.ph");

	element_pairing(verify.temp1, verify.sig, key.g);
	element_printf("f(sig, g) = %B\n", verify.temp1);

	element_pairing(verify.temp2, verify.h, key.X);
	element_printf("f(message hash, public_key) = %B\n", verify.temp2);

	if (!element_cmp(verify.temp1, verify.temp2)) {
		printf("signature verifies\n");
	} else {
		printf("*BUG* signature does not verify *BUG*\n");
	}
	return 1;
}

int read_file_tag(unsigned char *path){
	size_t len=strlen(path);
	unsigned char *file_tag=(unsigned char *)malloc((len+5)*sizeof(char));
	if(!file_tag){
		printf("malloc failed\n");
		return 0;
	}
	
	get_tag_name(file_tag,path);
	
	
	int i=0,ch;
	long int step=1;
	long int sum=0;
	
	FILE *fpkey=fopen(path, "r");
	if(!fpkey){
		printf("Cannot find file:%s\n",path);
		return 0;
	}

	while(1){
		sum=0;
		for(i=0;i<4;i++){
			ch=fgetc(fpkey);
			if(ch==EOF){
				break;
			}
			sum=sum*256+ch;
		}
		if(sum==0)break;
		
		len = sprintf(msg, "%ld", step); 
		element_from_hash(key.K, msg, len);

		element_random(key.v);
		//element_set_si(key.v, 2);
		//element_printf("%B\n",key.v);
		write_into_file(key.v, "ppdp.chal", "a");
		
		element_pow_zn(key.K, key.K, key.v);
		if(step==1){
			element_set(verify.h,key.K);
			element_set_si(key.sum,sum);
			
			element_mul(key.sum, key.v, key.sum);
			
		}else {
			element_mul(verify.h, verify.h, key.K);
			element_set_si(key.tmp,sum);
			
			
			element_mul(key.tmp, key.v, key.tmp);
			
			element_add(key.sum, key.sum, key.tmp);
		}
		
		step++;	
		if(ch==EOF)break;

	}
	
		
	element_pow_zn(key.u, key.u, key.sum);
	
	element_mul(verify.h, verify.h, key.u);

		
		
	write_into_file(verify.h, "ppdp.ph","w");	
	
	
	fpkey=fopen(file_tag,"r");
	if(!fpkey){
		printf("Cannot find file:%s\n",path);
		return 0;
	}
	FILE* fpchal=fopen("ppdp.chal", "r");

	int flag=1;
	while(fgets(msg,LENGTH,fpkey)){
		if(!element_set_str(key.K,msg,10)){
			printf("read file:%s error!\n",file_tag);
			return 0;
		}
		fgets(msg1, LENGTH, fpchal);
		//printf("*%s*",msg1);
		if(!element_set_str(key.v, msg1, 10)){
			printf("read file:%s error!\n", "ppdp.chal");
			return 0;
		}//element_printf("%B\n",key.v);
		
		if(flag){
			element_set(verify.sig, key.K);
			
			element_pow_zn(verify.sig, verify.sig, key.v);
			flag=0;

		}else {
			element_pow_zn(key.K, key.K, key.v);
			element_mul(verify.sig, verify.sig, key.K);
		}

		
	}write_into_file(verify.sig,"ppdp.sig","w");
	
	
	free(file_tag);
	return 1;
}

int verify_file(unsigned char *path){
	read_verify_param();

	if(check_proxy()){
		check_file(path);
		
		return 1;
	}
	
	return 0;
}