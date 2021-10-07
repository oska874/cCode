#include <iostream>
#include <memory>
#include <utility>

int main()
{
    auto important = std::make_unique<int>(1);
    auto add = [v1=1, v2=std::move(important)](int x, int y){
        return x+y+v1+(*v2);
    };
    std::cout<<add(3,4)<<std::endl;

    auto val = 101;
    auto cp_val = [&val] { val++;return val;};
    std::cout<<val<<std::endl;
    std::cout<<cp_val()<<" "<<val<<std::endl;

    auto cp_val2 = [&] { val++;std::cout<<"call "<<val<<std::endl;};
    cp_val2();

    auto cp_val3 = [=] { std::cout<<"call "<<val<<std::endl; return val;};
    cp_val3();
    std::cout<<val<<std::endl;

    auto add2 = [](auto x, auto y){ return x+y;};
    std::cout<<add2(1,2)<<" "<<add2(1.1,2.2)<<std::endl;

    return 0;
}
