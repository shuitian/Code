#include<iostream>
using namespace std;
using std::cin;
using std::cout;
class ecc{
    private:
        int mod,a,b;
    public:
        ecc(int mod,int a,int b){
            this->mod=mod;   
            this->a=a;
            this->b=b;
        }ecc(){
            mod=a=b=0;
        }friend class ecc_point;
        friend ecc_point operator * (ecc_point &a,int factor);
    
};
ecc f(11,1,6);
class ecc_point{
    private:
        int x,y;
    public:
        ecc_point(int x,int y){
            this->x=x;
            this->y=y;
        }ecc_point(){
            x=y=0;    
        }void show(){
            cout<<x<<' '<<y<<endl;   
        }
        void ecc_p_setx(int x){
            this->x=x;    
        }void ecc_p_sety(int y){
            this->y=y;
        }ecc_point operator + (ecc_point B);
        ecc_point operator - ();
        ecc_point operator - (ecc_point B);
        ecc_point operator = (ecc_point B);
        friend ecc_point operator * (ecc_point &a,int factor);
        friend ecc_point operator * (int factor,ecc_point &a);
        friend long inv(long f,long m);
        friend ecc_point fa(ecc_point a,long b);
};
ecc_point ecc_point::operator - (){
    return ecc_point(x,-y);
};
ecc_point ecc_point::operator + (ecc_point c){
    int lambda,newx,newy;
    if((c.x==0) && (c.y==0))return ecc_point(x,y);
    else if((x==0)&&(y==0))return c;
    else if((x==c.x)&&(y+c.y==0))return ecc_point();
    else {
        if((x==c.x)&&(y==c.y)){
            long yp=2*y,ypinv;
            yp%=f.mod;if(yp<0)yp+=f.mod;
            ypinv=inv(yp,f.mod);
            if(ypinv==0)return ecc_point();
            else {
                lambda=((3*x*x+f.a)*ypinv)%f.mod;
                newx=(lambda*lambda-2*x)%f.mod;
                if(newx<0)newx+=f.mod;
                newy=(lambda*(x-newx)-y)%f.mod;
                if(newy<0)newy+=f.mod;
//cout<<ypinv<<' '<<lambda<<' '<<newx<<' '<<newy<<endl;
                return ecc_point(newx,newy);
            }
        }
        else {
            long yp=c.x-x,ypinv;
            yp%=f.mod;if(yp<0)yp+=f.mod;
            ypinv=inv(yp,f.mod);
            if(ypinv==0)return ecc_point();
            else {
                lambda=(ypinv*(c.y-y))%f.mod;
                if(lambda<0)lambda+=f.mod;
                newx=lambda*lambda-x-c.x;
                newy=lambda*(x-newx)-y;
                newx=newx%f.mod;
                if(newx<0)newx+=f.mod;
                newy=newy%f.mod;
                if(newy<0)newy+=f.mod;
                return ecc_point(newx,newy);
            }
        }
    }
};ecc_point ecc_point::operator - (ecc_point B){
    return    *this+(-B);
};ecc_point ecc_point::operator = (ecc_point B){
    x=B.x;y=B.y;
    return *this;  
};
ecc_point operator * (ecc_point &a,int factor){
    return fa(a,factor);
};
ecc_point operator * (int factor,ecc_point &a){
    return a*factor;   
};
ecc_point  fa(ecc_point a,long b){//a^b mod m
        ecc_point s;
        while(b){
             if(b&1)s=s+a;a=a+a;b>>=1;
        }return s;
};
long inv(long f, long m){
	static long gcdInvOutArr[2]={0,0};    	//gcdInvOutArr[0]存放gcd(a,m), gcdInvOutArr[1]存放乘法逆元
	long a[3]={1,0,m},b[3]={0,1,f},t[3]={0,0,0},q,i;
	while(1){
		if(b[2]==0){gcdInvOutArr[0]=a[2];gcdInvOutArr[1]=0;break;}//没有乘法逆元
		if(b[2]==1){
			while(b[1]<0)b[1]+=m;
			gcdInvOutArr[0]=b[2];
			gcdInvOutArr[1]=b[1];
			break;
		}q=a[2]/b[2];
		for(i=0;i<3;i++){
			t[i]=a[i]-b[i]*q;
			a[i]=b[i];
			b[i]=t[i];
		}
	}
	return gcdInvOutArr[1];
};
int main(){
    
    system("pause");
    return 0;   
}
