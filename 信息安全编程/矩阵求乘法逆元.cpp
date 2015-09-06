#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
class matrix22{
    private:
        int a[2][2];
    public:
        void set(int b,int i,int j){
            a[i-1][j-1]=b;
        }void setall(int q,int w,int e,int r){
            a[0][0]=q;a[0][1]=w;a[1][0]=e;a[1][1]=r;
        }int get(int i,int j){
            return    a[i-1][j-1];
        }int getdet(){
            return a[0][0]*a[1][1]-a[0][1]*a[1][0];
        }void dispaly(){
            cout<<a[0][0]<<' '<<a[0][1]<<endl;   
            cout<<a[1][0]<<' '<<a[1][1]<<endl;
        }
        matrix22(){this->setall(0,0,0,0);};
        matrix22 (int q,int w,int e,int r){
            this->setall(q,w,e,r);
        }matrix22 operator +(matrix22 &A);
        matrix22 operator -(matrix22 &A);
        matrix22 operator *(matrix22 &A);
        friend void inverse(int x,int y);
};
matrix22 matrix22::operator +(matrix22 &A){
            matrix22 c;
            int i,j;
            for(i=0;i<2;i++)
            for(j=0;j<2;j++){
                c.a[i][j]=A.a[i][j]+a[i][j];
            }return matrix22(c.a[0][0],c.a[0][1],c.a[1][0],c.a[1][1]);
};
matrix22 matrix22::operator -(matrix22 &A){
            matrix22 c;
            int i,j;
            for(i=0;i<2;i++)
            for(j=0;j<2;j++){
                c.a[i][j]=a[i][j]-A.a[i][j];
            }return matrix22(c.a[0][0],c.a[0][1],c.a[1][0],c.a[1][1]);
};
matrix22 matrix22::operator *(matrix22 &A){
            matrix22 c;
            c.a[0][0]=A.a[0][0]*a[0][0]+A.a[1][0]*a[0][1];
            c.a[0][1]=A.a[0][1]*a[0][0]+A.a[1][1]*a[0][1];
            c.a[1][0]=A.a[0][0]*a[1][0]+A.a[1][0]*a[1][1];
            c.a[1][1]=A.a[0][1]*a[1][0]+A.a[1][1]*a[1][1];
            return matrix22(c.a[0][0],c.a[0][1],c.a[1][0],c.a[1][1]);
};
void inverse(int x,int y){
    
}
int main(){
    
    system("pause");
    return 0;
}
