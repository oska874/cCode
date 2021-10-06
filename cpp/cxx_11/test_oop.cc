#include <iostream>

class VBase{
    virtual void foo(int);
    virtual void foo(float);
};

class Sub2: public VBase{
    virtual void foo(int) override;
    //virtual void foo(float) override;
};

class Sub3 final: public VBase{
    virtual void foo(float) override;
};
class Sub4:public Sub2{};
//class Sub5:public Sub3{};

class Magic{
    public:
        Magic() = default;
        Magic& operator=(const Magic&) = delete;
        Magic(int num);
};

enum class new_enum : unsigned int {
    val0,
    val1,
    val2,
    val3 = 100,
    val4 = 99,
};

class Base{
    public:
        int val1;
        int val2;
        Base() { val1 = 1;}
        Base(int val):Base(){ val2 = val;}
};

class SubClass: public Base{
    public:
        using Base::Base;
};


int main()
{
    Base b(2);
    std::cout<<b.val1<<" "<<b.val2<<std::endl;

    SubClass s(3);
    std::cout<<s.val1<<" "<<s.val2<<std::endl;

    if(new_enum::val3 == new_enum::val4)
    {
        std::cout<<"equal"<<std::endl;
    }
    else
    {
        std::cout<<"n equal"<<std::endl;
    }
    return  0;
}
