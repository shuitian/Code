#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class ecc{
    private:
        int mod,a,b;
    public:
        ecc();
        ecc(int mod,int a,int b);
        friend class ecc_point;
        friend ecc_point operator * (ecc_point &a,int factor);
    
};
ecc::ecc(){
    ecc(0,0,0);
};
ecc::ecc(int mod,int a,int b){
    this->mod=mod;   
    this->a=a;
    this->b=b;   
};
ecc f(11,1,6);
class ecc_point{
    private:
        int x,y;
    public:
        ecc_point(int x,int y);
        ecc_point();
        void show();
        void ecc_p_setx(int x);
        void ecc_p_sety(int y);
        ecc_point operator + (ecc_point B);
        ecc_point operator - ();
        ecc_point operator - (ecc_point B);
        ecc_point operator = (ecc_point B);
        //Clean Code Add Function
        //void PointAddPointZero(ecc_point NeddAdd);
        ecc_point PointAddPointEqual(ecc_point NeedAdd);
        ecc_point PointAddPointEqual_InvNotNull(ecc_point NeedAdd,long yp,long ypinv);
        ecc_point PointAddPointNormal(ecc_point NeedAdd);
        ecc_point PointAddPointNormal_InvNotNull(ecc_point NeedAdd,long yp,long ypinv);
        //Clean Code Add Function Down
        friend ecc_point operator * (ecc_point &a,int factor);
        friend ecc_point operator * (int factor,ecc_point &a);
        friend long inv(long f,long m);
        friend ecc_point fa(ecc_point a,long b);
};
ecc_point::ecc_point(int x,int y){
    this->x=x;
    this->y=y;
};
ecc_point::ecc_point(){
    ecc_point(0,0);
};
void ecc_point::show(){
    cout<<this->x<<' '<<this->y<<endl;  
};
void ecc_point::ecc_p_setx(int x){
    this->x=x;
};
void ecc_point::ecc_p_sety(int y){
    this->y=y;
};
ecc_point ecc_point::operator - (){
    return ecc_point(x,-y);
};

ecc_point ecc_point::operator + (ecc_point c){
    if((c.x==0) && (c.y==0))return ecc_point(x,y);
    else if((x==0)&&(y==0))return c;
    else if((x==c.x)&&(y+c.y==0))return ecc_point();
    else if((x==c.x)&&(y==c.y))return PointAddPointEqual(c);
    else return PointAddPointNormal(c);
};
//point + point function is too big and complex
//Clean Code Mission Start
//void PointAddPointZero();
ecc_point ecc_point::PointAddPointEqual(ecc_point c){
    long yp=(2*y)%f.mod,ypinv=inv(yp,f.mod);
    if(ypinv==0)return ecc_point();
    else return PointAddPointEqual_InvNotNull(c,yp,ypinv);
};
ecc_point ecc_point::PointAddPointEqual_InvNotNull(ecc_point c,long yp,long ypinv){
    int lambda=((3*x*x+f.a)*ypinv)%f.mod,
        newx=(((lambda*lambda-2*x)%f.mod)+f.mod)%f.mod,
        newy=(((lambda*(x-newx)-y)%f.mod)+f.mod)%f.mod;
    return ecc_point(newx,newy);       
};
ecc_point ecc_point::PointAddPointNormal(ecc_point c){
    long yp=(c.x-x)%f.mod,ypinv=inv(yp,f.mod);
    if(ypinv==0)return ecc_point();
    else return PointAddPointNormal_InvNotNull(c,yp,ypinv);
};
ecc_point ecc_point::PointAddPointNormal_InvNotNull(ecc_point c,long yp,long ypinv){
    int lambda=(((ypinv*(c.y-y))%f.mod)+f.mod)%f.mod,
        newx=(((lambda*lambda-x-c.x)%f.mod)+f.mod)%f.mod,
        newy=(((lambda*(x-newx)-y)%f.mod)+f.mod)%f.mod;
    return ecc_point(newx,newy);   
};
//Clean Code Mission Complete
ecc_point ecc_point::operator - (ecc_point B){
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
        s.show();
        printf("*******\n");
        while(b){
             if(b&1)s=s+a;a=a+a;b>>=1;
        }return s;
};
long inv(long f, long m){
	static long gcdInvOutArr[2]={0,0};    	//gcdInvOutArr[0]存放gcd(a,m), gcdInvOutArr[1]存放乘法逆元
	if(f<0)f+=m;
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
