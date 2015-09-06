#include "ppdp.h"

int main(int argc, char **argv) {
	int opt=-1;
	
	ppdp_init();

	if(argc < 2 )return -1;
	
	while((opt = getopt_long(argc, argv, "kt:v:", longopts, NULL)) != -1){
		switch(opt){
			case 'k':
				if(!create_key())printf("Couldn't create keys\n");
				break;
			
			case 't':
				if(!tag_file(optarg))printf("Couldn't tag file\n");
				break;

			case 'v':
				if(!verify_file(optarg))printf("Couldn't verify file\n");
				break;
			
			default:
				break;
		}
	}
	ppdp_clean();
	return 0;
}
