#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int a = 4, b = 5;
    std::function<int(void)> supply = [=]() -> int {
        return a;
    };

    function<void(int)> consumer = [&](int in) {
        a = 0;
        b = 0;
        cout << "consuming value: " << b << endl;
    };

    function<int(int)> func = [&](int in) -> int {
        return in * b;
    };

    function<int(int)> func2 = [=](int in) -> int {
        return in * b;
    };

    cout << "value from supply is: " << supply() << endl;
    cout << "a and b are: " << a << ", " << b << endl;
    consumer(9);
    cout << "a and b are: " << a << ", " << b << endl;
    cout << "value from supply is: " << func(10) << endl;
    cout << "a and b are: " << a << ", " << b << endl;
    cout << "value from supply is: " << func2(10) << endl;
    cout << "a and b are: " << a << ", " << b << endl;

    int num = 100;

    // Lamnda is const function, use `mutable` can cancel const
    //auto fun = [=](){ num = 200; cout << num << endl; };
    auto fun = [=]() mutable { num = 200; cout << num << endl; };
    fun();
    // num = 100
    cout << num << endl;

    vector<int> v1 = {1,2,3,4,5,6,7,8};
    auto func3 = [](int num){cout<<num<<endl;};
    for_each(v1.begin(), v1.end(), func3);
    cout<<"-------------\n";

    for_each(v1.begin(), v1.end(), [&](int num){num+=1;});

    for_each(v1.begin(), v1.end(), func3);
    cout<<"-------------\n";

    return 0;
}
