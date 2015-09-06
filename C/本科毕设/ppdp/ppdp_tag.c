#include "ppdp.h"

int read_tag_param(){
	read_from_file(key.u, "ppdp.u");	
	read_from_file(key.x, "ppdp.x");
			
	return 1;
}

int get_tag_name(unsigned char * file_tag, unsigned char *path){
	
	size_t len=strlen(path);
	strncpy(file_tag,path,len);
	strncpy(file_tag+len,".tag",5);
	
	
	return 1;
}

int clear_file(unsigned char * file){
	
	FILE* fpkey=fopen(file, "w");
	if(!fpkey){
		printf("Cannot find file:%s\n",file);
		return 0;
	}
	fclose(fpkey);
	
	return 1;
}

int tag(unsigned char * file_tag, unsigned char *path){

	size_t len;
	int i=0,ch;
	long int step=1;
	long int sum=0;
	
	FILE* fpkey=fopen(path, "r");
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
		element_set_si(key.sum,sum);
		
		len = sprintf(msg, "%ld", step); 
		element_from_hash(verify.h, msg, len);
		
		element_pow_zn(key.K, key.u, key.sum);
		element_mul(verify.h, verify.h, key.K);
		
		element_pow_zn(verify.h, verify.h, key.x);
		
		write_into_file(verify.h, file_tag,"a");	
		
		step++;
		
		if(ch==EOF)break;
		
	}
	return 1;

}

int create_file_tag(unsigned char *path){
	
	size_t len=strlen(path);
	unsigned char *file_tag=(unsigned char *)malloc((len+5)*sizeof(char));
	if(!file_tag){
		printf("malloc failed\n");
	}
	
	get_tag_name(file_tag, path);
	clear_file(file_tag);
	tag(file_tag, path);
	
	free(file_tag);
	return 1;
}

int tag_file(unsigned char *path){
	
	if(!read_tag_param()){
		printf("read_tag_param failed!\n");
		return 0;
	}
	if(!create_file_tag(path)){
		printf("create_file_tag failed!\n");
		return 0;
	}
	printf("tag file success!\n");
		
	
	return 1;
}