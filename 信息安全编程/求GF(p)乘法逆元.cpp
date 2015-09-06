#include<iostream>
using namespace std;
class matrix13{
    private:
        int a,b,c;
    public:
        int geta(){
            return this->a;   
        }int getb(){
            return this->b;   
        }int getc(){
            return this->c;   
        }void seta(int a){
            this->a=a;
        }void setb(int b){
            this->b=b;
        }void setc(int c){
            this->c=c;
        }matrix13(int a,int b,int c){
            this->seta(a);   
            this->setb(b);   
            this->setc(c);   
        }matrix13(){
            this->seta(0);   
            this->setb(0);   
            this->setc(0);
        };
        friend matrix13 operator + (matrix13 z,matrix13 x);
        friend matrix13 operator - (matrix13 z,matrix13 x);
        friend matrix13 operator * (matrix13 z,int x);
        matrix13 operator = (matrix13 x);
        matrix13 operator - ();
};
matrix13 operator + (matrix13 z,matrix13 x){
    return matrix13(z.geta()+x.geta(),z.getb()+x.getb(),z.getc()+x.getc());
}matrix13 operator - (matrix13 z,matrix13 x){
    return matrix13(z.geta()-x.geta(),z.getb()-x.getb(),z.getc()-x.getc());
}matrix13 operator * (matrix13 z,int x){
    return matrix13(z.geta()*x,z.getb()*x,z.getc()*x);
}matrix13 matrix13::operator -(){
    return matrix13(-a,-b,-c);
}matrix13 matrix13::operator = (matrix13 x){
    this->seta(x.geta());
    this->setb(x.getb());
    this->setc(x.getc());
}
long getinverse(long m,long f){
    matrix13 a(1,0,m),b(0,1,f),t;
    long q;
    while(1){
        if(b.getc()==0)return 0;
        if(b.getc()==1){
            while(b.getb()<0)b.setb(b.getb()+m);
            return b.getb();
        }
        q=a.getc()/b.getc();
        t=a-b*q;
        a=b;
        b=t;
    }
    return 0;    
}
int main(){ 
    long a,b,c;
    while(1){
        cout<<"请输入两个正整数m和b:求正整数r，使r*b≡1 (mod m)"<<endl;
        cin>>a>>b;
        c=getinverse(a,b);
        if(c==0) cout<<"没有乘法逆元"<<endl;
        else cout<<c<<endl; 
    }
    system("pause");
    return 0;
}
