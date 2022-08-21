#include <iostream>

using namespace std;

class testA{
    int val;
    int key;
};

class testB:public testA{
    int num;
};

class Base { virtual void dummy_fun() {} };
class Derived : public Base {};

int main()
{
    int n_ori;
    int *np_ori;
    unsigned int un_ori;
    unsigned int *unp_ori;
    int *r_ori=&n_ori;
    void *pv;

    testA *p_a=new testA;
    testB *p_b=new testB;
    testB *p_c;
    testA *p_d;

    Base* b1 = new Derived;
    Base* b2 = new Base;
    Derived* d1 = dynamic_cast<Derived *>(b1);          // succeeds
    Derived* d2 = dynamic_cast<Derived *>(b2);          // fails: returns 'NULL'

    const int *p_i1;
    int *p_i2;

    n_ori =1024;
    un_ori = 333;

    np_ori = &n_ori;
    unp_ori = &un_ori;

    cout<<"np_ori"<<*np_ori<<endl;
    cout<<"n_ori"<<n_ori<<endl;
    cout<<"unp_ori"<<*unp_ori<<endl;
    cout<<"un_ori"<<un_ori<<endl;
    cout<<endl;

    np_ori = reinterpret_cast<int*>(unp_ori);
    un_ori = static_cast<unsigned int>(n_ori);

    cout<<"np_ori"<<*np_ori<<endl;
    cout<<"n_ori"<<n_ori<<endl;
    cout<<"unp_ori"<<*unp_ori<<endl;
    cout<<"un_ori"<<un_ori<<endl;
    cout<<endl;

    //p_c=dynamic_cast<testB *>(p_a);//fail
    p_d=dynamic_cast<testA *>(p_b);

    cout<<"p_c"<<p_c<<endl;
    cout<<"p_d"<<p_d<<endl;

    cout<<"d1"<<d1<<endl;
    cout<<"d2"<<d2<<endl; //NULL 0

    p_i1=&n_ori;
    //*p_i1=999;//not permit
    p_i2=const_cast<int*>(p_i1);
    *p_i2=999;
    p_i1=const_cast<const int *>(p_i2);

    cout<<"p_i1"<<*p_i1<<endl;

    


    return 0;
}
