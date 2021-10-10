#include <iostream>
#include <vector>
#include <algorithm>

#if 0
//?
template<typename T, typename... Ts>
auto printf3(T value, Ts... args)
{
    std::cout<<value<<std::endl;
    (void)std::initializer_list<T>{
        ([&args]{ std::cout<<args<<std::endl;}(), value)...
    };
}
#endif

template <auto X>
void buffs2()
{
    std::cout<<X<<std::endl;
}

template<typename T, int size>
auto buffs(T val)
{
    return sizeof(val)*size;
}

template<typename ...T>
auto sum(T ... t)
{
    return (t+...);
}

template <typename T>
auto print_type_info(const T& p)
{
    auto &type = typeid(p);
    std::cout<<type.name()<<std::endl;
    auto &type2 = typeid(T);
    std::cout<<type2.name()<<std::endl;
    if constexpr (std::is_integral<T>::value)
    {
        return p+1;
    }
    else
    {
        return p+0.0001;
    }
}

template <typename... TS>
void magic(TS... args)
{
    std::cout<<sizeof...(args)<<std::endl;
}

int main()
{
    std::cout<<"int "<<print_type_info<double>(10)<<std::endl;
    std::cout<<"float "<<print_type_info<float>(10.1)<<std::endl;


    std::vector<int> vec = {1,2,3,4,5,};
    if(auto itr =std::find(vec.begin(), vec.end(), 3);itr!=vec.end())
        *itr = 100;
    std::cout<<"xxxxx "<<std::endl;
    for(auto elm:vec)
    {
        std::cout<<elm<<std::endl;
    }
    for(auto &elm:vec)
    {
        elm+=1000;
    }
    std::cout<<"yyyy "<<std::endl;
    for(auto elm:vec)
    {
        std::cout<<elm<<std::endl;
    }

    magic();
    magic(1);
    magic(1,2,3);
    magic(1,2,3,4,5,6,7,8,9,0);

    //printf3(1,2,3,4);
    std::cout<<sum(1,2,3)<<std::endl;

    std::cout<<buffs<double, 10>(10)<<std::endl;
    buffs2<10>();
    return 0;
}
