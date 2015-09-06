#include "ppdp.h"

int read_from_file(element_t e,char *path){
	FILE *fpkey=fopen(path,"r");
	if(!fpkey){
		printf("Couldn't open %s\n",path);
		return 0;
	}
	
	//fseek(fpkey, 0L,SEEK_END); 
	//size_t len =ftell(fpkey);
	char *tmp=(char *)malloc(PARAMLENGTH*sizeof(char)+3);
	if(!tmp){
		printf("malloce failed\n");
		return 0;
	}
	//fseek(fpkey,0L,SEEK_SET);
	fgets(tmp,PARAMLENGTH+1,fpkey);
	
	//fread(tmp,1,len,fpkey);
	//printf("*%s*\n",tmp);
	if(!element_set_str(e,tmp,10)){
		printf("element_set_str failed\n");
		return 0;
	}
	free(tmp);
	fclose(fpkey);
	return 1;
}

int write_into_file(element_t e, char *path, char *param){
	FILE *fpkey=fopen(path, param);
	if(!fpkey){
		printf("Couldn't open %s\n",path);
		return 0;
	}
	element_out_str(fpkey,10,e);
	if(param[0]=='a'){
		fprintf(fpkey,"\n");
	}
	fclose(fpkey);
	return 1;
}


	
