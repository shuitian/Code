#include <stdio.h>

long  my_oper(int  *result,  int  num1,  int  num2 ,  char  * op){
	if(*op == '+'){
		*result = num1+num2;
	}else if(*op == '-'){
		*result = num1-num2;
	}else if(*op == '*'){
		*result = num1*num2;
	}else if(*op == '/'){
		*result = num1/num2;
	}else {
		*result = -2;
	}
	return 0;
}

int main(){
	int num1 = 10;
	int num2 = 5;
	int result ;
	my_oper(&result,num1,num2,"+");
	printf("%d\n",result);
	my_oper(&result,num1,num2,"-");
	printf("%d\n",result);
	my_oper(&result,num1,num2,"*");
	printf("%d\n",result);
	my_oper(&result,num1,num2,"/");
	printf("%d\n",result);
	return 0;
}