#include <iostream>
#include <vector>
#include <cstring>
#include <typeinfo>


int foo1(auto x, auto y)
{
    std::cout <<"foo1"<<std::endl;
    return x+y;
}

int foo1(int x, int y)
{
    std::cout <<"foo1 2"<<std::endl;
    return x+y;
}

template <typename R2, typename R3>
auto add2(R2 x, R3 y)
{
    return x+y;
}
template <typename R1, typename R2, typename R3>
R1 add(R2 x, R3 y)
{
    return x+y;
}

int main()
{
    std::vector<int> xx = {1,2,3,4,};
    for(auto itr = xx.begin();itr != xx.end();itr++)
    {
        std::cout<<"vec "<< *itr << std::endl;
    }

    auto xx2 = 1;
    auto xx3 = 1.0;
    auto xx4 = "1.00";

    std::cout << xx2 << " " << xx3 << " " << xx4 <<std::endl;

    auto xx5 = new int(100); //cppchek can check exceed with specific type
    auto xx6 = new auto(100); //cppchek can not check auto type array exceed
    std::memset(xx5, 0xaa, 100);
    std::memset(xx6, 0xbb, 100);
    
    for(int i=0;i<1101;i++)
    {
     //   std::cout<<"zz " << xx6[i] <<std::endl;
    }

    for(int i=0;i<1101;i++)
    {
        xx5[i] = i;
    }
    for(int i=0;i<1101;i++)
    {
    //    std::cout<<xx5[i] <<std::endl;
    }
    for(int i=0;i<1101;i++)
    {
    //    std::cout<<"xx "<< xx6[i] <<std::endl;
    }

    std::cout << "xx5 size "<<sizeof(xx5)<<std::endl;

    auto &xx5_type = typeid(xx5);
    std::cout << xx5_type.name()<<std::endl;
    auto &xx5_type2 = typeid(xx5[0]);
    std::cout << xx5_type2.name()<<std::endl;
    auto &xx4_type = typeid(xx4);
    std::cout << xx4_type.name()<<std::endl;
    auto &xx3_type = typeid(xx3);
    std::cout << xx3_type.name()<<std::endl;

    int *xx7 = new int(10);
    std::memset(xx7, 0x11, 11);
    for(auto i=0;i<100;i++)
    {
        std::cout<<"yy "<<xx7[i]<<std::endl;
    }

    int x =1;
    float y = 2.0;
    std::cout<< foo1(x,y)<<std::endl;
    int z = 2;
    std::cout<< foo1(x,z)<<std::endl;


    decltype(x+y) xz2;
    if(std::is_same<decltype(x), int>::value)
    {
        std::cout<<"x is int"<<std::endl;
    }
    if(std::is_same<decltype(y), decltype(xz2)>::value)
    {
        std::cout<<"y equal xz2"<<std::endl;
    }
    if(std::is_same<decltype(x), decltype(xz2)>::value)
    {
        std::cout<<"x equal xz2"<<std::endl;
    }
    else
    {
        std::cout<<"x not equal xz2"<<std::endl;
    }

    auto &ar2 = typeid(add<int, int, double>(1,2.0));
    std::cout<<"t2 "<< ar2.name()<<std::endl;
    auto &ar3 = typeid(add2<int, double>(1,2.0));
    std::cout<<"t3 "<< ar3.name()<<std::endl;
    return 0;
}

