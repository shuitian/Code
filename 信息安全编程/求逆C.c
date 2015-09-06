#include<stdio.h>
long getinver(long m,long d){//b[2]最大公约数
	long a[3]={1,0,m},b[3]={0,1,d},t[3]={0,0,0},q,i;
	while(1){
		if(b[2]==0)return 0;//没有乘法逆元
		if(b[2]==1){
			while(b[1]<0)b[1]+=m;
			return b[1];
		}q=a[2]/b[2];
		//
		if(a[2]==b[2]*q){
            while(b[1]<0)b[1]+=m;
            printf("GCD:%d ",b[2]);
			return b[1];   
        }
		//
		for(i=0;i<=2;i++){
			t[i]=a[i]-b[i]*q;
			a[i]=b[i];
			b[i]=t[i];
		}
	}
	return 0;
}
int main(){
	long m,b,r;
	while(1){
		scanf("%ld%ld",&m,&b);	
		r=getinver(m,b);
		if(r==0)printf("没有乘法逆元\n");
		else printf("乘法逆元为%ld\n",r);
	}
	return 0;
}
