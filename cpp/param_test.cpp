#include <iostream>
using namespace std;

int add1(int x=10,int y=20)
{
    return x+y;
}

void add2(int &a,int b,int c)
{
    a=b+c;
}

int &add3(int a,int b)
{
    int x= a+b;
    return &x;
}

int main()
{
    cout<<add1()<<endl;
    cout<<add1(1)<<endl;
    cout<<add1(1,2)<<endl;
    int x=10,y=11,z=12;
    cout<<"x="<<x<<endl;
    add2(x,y,z);
    cout<<"x2="<<x<<endl;
    x = add3(y,z);
    cout<<"x3="<<x<<endl;

    return 0;
}

