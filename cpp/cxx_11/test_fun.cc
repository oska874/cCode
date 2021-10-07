#include <iostream>

using foo = void(int);
void fun(foo f)
{
    std::cout<<"foo"<<std::endl;
    f(1);
}

int main()
{
    auto f = [](int val){ std::cout<<"close: "<<val<<std::endl;};
    fun(f);
    std::cout<<"----------"<<std::endl;
    f(1);

    return 0;
}
