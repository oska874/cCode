#include <iostream>
#include <vector>
#include <algorithm>

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

    return 0;
}
