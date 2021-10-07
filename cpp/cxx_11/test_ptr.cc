#include <iostream>
#include <memory>

void foo(std::shared_ptr<int> i)
{
    (*i)++;
}

int main()
{

    auto ptr = std::make_shared<int>(10);
    foo(ptr);
    std::cout<<*ptr<<std::endl;

    auto ptr2 = ptr;
    auto ptr3 = ptr2;
    auto *p = ptr.get();

    std::cout<<"----------------------\n";
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr2.use_count()<<std::endl;
    std::cout<<ptr3.use_count()<<std::endl;

    std::cout<<"----------------------\n";
    ptr2.reset();
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr2.use_count()<<std::endl;
    std::cout<<ptr3.use_count()<<std::endl;

    std::cout<<"----------------------\n";
    ptr3.reset();
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr2.use_count()<<std::endl;
    std::cout<<ptr3.use_count()<<std::endl;

    std::cout<<"----------------------\n";
    ptr.reset();
    std::cout<<ptr.use_count()<<std::endl;
    std::cout<<ptr2.use_count()<<std::endl;
    std::cout<<ptr3.use_count()<<std::endl;
    return 0;
}
