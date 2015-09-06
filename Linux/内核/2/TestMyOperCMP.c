#include <linux/unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <time.h>
#define  _NR_my_oper    317
//#define  _NR_my_oper    60
//__syscall4(long, my_oper, int *, result, int, num1, int num2, char*,op);
int main(){
	int num1 = 10;
	int num2 = 5;
	int result ;
	int i;
	time_t *t;
	long _t = (long)(time(t));
	printf("%ld",_t);
	for(i=0;i<10000;i++){
		syscall(_NR_my_oper, &result, num1, num2, "+");
	}
	long _t1 = (long)(time(t));
	printf("%ld",_t1-_t);
	for(i=0;i<10000;i++){
		result = num1+num2;
	}
	long _t2 = (long)(time(t));
	printf("%ld",_t2-_t1);
	//syscall(_NR_my_oper, 0);
	//printf("0\n");
	//printf("%d\n",result);
	return 0;
}