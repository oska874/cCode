#include <iostream>
#include <typeinfo>
#include <vector>
#include <iterator>

using namespace std;

auto sumsum(float a, float b) ->float //c++11
//auto sumsum(float a, float b) //c++14
{
    return a+b;
}

int main()
{
    auto str = "hello";
    auto iint = 123;
    auto ff = 3.13f;
    decltype(ff) ff2 = 3.13d;

    cout << str << endl << typeid(str).name() << endl;
    cout << iint << endl << typeid(iint).name() << endl;
    cout << ff << endl << typeid(ff).name() << endl;
    cout << ff2 << endl << typeid(ff2).name() << endl;

    auto x1 = sumsum(1.1f, 2.2f);
    cout << x1 << " " << typeid(x1).name() <<endl;

    auto &x2 = x1;
    x2 = 0;
    cout << x1<<endl;

    vector<int> v1 = {0,1,2,3,4};
    auto vit = v1.end();
    
    //cout << vit << endl;
    return 0;
}
