#include <iostream>
using namespace std;


namespace domain_test{
    int gi=7;
    int gii=9;
}
namespace dt = domain_test;
using dt::gii;
int gi = 0;
int main()
{
    do{
        int gi=4;
        cout<<"B:"<<gi<<endl;
    }while(0);
    cout<<"C:"<<gi<<endl;
    {
        int gi =5;
        cout<<"A:"<<gi<<endl;
    }
    gi =9;
    cout<<"D:"<<gi<<endl;
    cout<<"E:"<<dt::gi<<endl;
    cout<<"F:"<<gii<<endl;

    return 0;
}

