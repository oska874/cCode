#include <iostream>
using namespace std;


class base {
    public:
    int fun_a(int m,int n){cout <<"base1"<<endl;return 0;}
    int fun_b(int m,int n){cout <<"base2"<<endl;return 0;}
    virtual int fun_c(int m,int n){cout <<"base3"<<endl;return 0;}
    int fun_b(double m,double n){cout<<"base4:overload"<<endl;return 0;}
};

class derive:public base{
    public:
    int fun_a(int m,int n){cout <<"derive redefine"<<endl;return 0;}
    int fun_b(int m,double n){cout <<"derive overload"<<endl;return 0;}
    int fun_b(float m,float n){cout <<"derive overload2"<<endl;return 0;}
    int fun_c(int m,int n){cout <<"derive override"<<endl;return 0;}
};

int main()
{
    base *ba=new base;
    derive *da=new derive;
    float m=0.1;
    double n=0.0;
    int p,q;

    ba->fun_a(p,q);
    ba->fun_b(p,q);
    ba->fun_c(p,q);
    ba->fun_b(m,m);

    da->fun_a(p,q);
    da->fun_b(p,n);//int,double
    da->fun_b(m,m);//float,float
    da->fun_c(p,q);

    return 0;
}
