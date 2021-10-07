#include <iostream>
#include <functional>
#include <utility>
#include <vector>
#include <string>

class A {
    public:
        int *ptr;
        A():ptr(new int(1)){ std::cout<<"construct"<<ptr<<std::endl;}
        A(A& a):ptr(new int(*a.ptr)){ std::cout<<"cp"<<ptr<<std::endl;}
        A(A&& a):ptr(a.ptr){ a.ptr=nullptr; std::cout<<"mov"<<ptr<<std::endl;}
        ~A(){ std::cout<<"desconstruct"<<ptr<<std::endl;}
};

A return_rval(bool test)
{
    std::cout<<"1"<<std::endl;
    A a;
    std::cout<<"2"<<std::endl;
    A b;
    std::cout<<"3"<<std::endl;
    if(test)
    {
        std::cout<<"a"<<std::endl;
        return a;
    }
    else
    {
        std::cout<<"b"<<std::endl;
        return b;
    }
}

using foo = void(int);
void fun(foo f)
{
    std::cout<<"foo"<<std::endl;
    f(1);
}

int foo2(int para)
{
    return para;
}

int foo3(int a, int b, int c)
{
    std::cout<<"cal foo3:"<<std::endl;
    std::cout<<"a:"<<a<<"b:"<<b<<"c:"<<c<<std::endl;
}

void ref(int& str)
{
    std::cout<<"i lval:"<<str<<std::endl;
}

void ref(int&& str)
{
    std::cout<<"i rval:"<<str<<std::endl;
}

void ref(std::string& str)
{
    std::cout<<"lval:"<<str<<std::endl;
}

void ref(std::string&& str)
{
    std::cout<<"rval:"<<str<<std::endl;
}

template <typename T>
void pass(T&& v)
{
    std::cout<<"normal pass:";
    ref(v);
    std::cout<<"move pass:";
    ref(std::move(v));
    std::cout<<"forward pass:";
    ref(std::forward<T>(v));
    std::cout<<"static cast pass:";
    ref(static_cast<T&&>(v));
}

int main()
{
    auto f = [](int val){ std::cout<<"close: "<<val<<std::endl;};
    fun(f);
    std::cout<<"----------"<<std::endl;
    f(1);

    std::function<int(int)> func = foo2;
    int important = 10;
    std::function<int(int)>func2 = [&](int val)->int{ return val+important+1;};
    std::cout<<func(10)<<" | "<<func2(10)<<std::endl;

    auto bind_foo = std::bind(foo3, std::placeholders::_1, 2,3);
    bind_foo(1);

    auto bind_foo2 = std::bind(foo3, std::placeholders::_1, std::placeholders::_2, 4);
    bind_foo2(10,11);

    auto bind_foo3 = std::bind(foo3, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    bind_foo3(9,10,11);

    auto bind_foo4 = std::bind(foo3, 1,2,3);
    bind_foo4(9,10,11);

    std::string lv1 = "str1";
    std::string&& rv1 = std::move(lv1);
    std::cout<<rv1<<std::endl;
    std::cout<<lv1<<std::endl;

    const std::string& lv2=lv1+lv1;
    std::cout<<lv2<<std::endl;
    //lv2 +="tst";
    std::string&& rv2 = lv1+lv2;
    std::cout<<rv2<<std::endl;
    rv2 += "test";
    std::cout<<rv2<<std::endl;

    ref(rv2);

    A obj = return_rval(false);
    std::cout<<"obj:"<<std::endl;
    std::cout<<obj.ptr<<std::endl;
    std::cout<<*obj.ptr<<std::endl;

    std::string stgr = "hel word";
    std::vector<std::string> vv;
    vv.push_back(stgr);
    std::cout<<"str: "<<stgr<<std::endl;
    vv.push_back(std::move(stgr));
    std::cout<<"str2: "<<stgr<<std::endl;

    pass(1);

    int l=2;
    pass(l);

    return 0;
}
