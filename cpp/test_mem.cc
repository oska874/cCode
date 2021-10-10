#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <chrono>

std::atomic<int> cnt = {0};

struct A {
    float x;
    int y;
    long long z;
};

int main()
{
    int a =0;
    int flag = 0;

    std::thread t1([&]() {
            int b = 0;
            std::cout<<"b:"<<b<<std::endl;
            while(flag != 1)
            {
            ;
            }

            b = a;
            std::cout<<"b:"<<b<<std::endl;
            });

    std::thread t2([&](){
            a = 5;
            flag = 1;
            });

    t1.join();
    t2.join();

    std::thread t3([]() {
            cnt.fetch_add(1);
            });
    std::thread t4([]() {
            cnt++;
            cnt+=1;
            });

    t3.join();
    t4.join();
    std::cout<<"cnt:"<<cnt<<std::endl;

    std::atomic<A> as;
    std::atomic<long long> as2;
    std::atomic<double> as3;
    std::cout<<"xxx:"<<std::boolalpha<<as.is_lock_free()<<"||"<<as2.is_lock_free()<<"||"<<as3.is_lock_free()<<std::endl;

    cnt = 0;
    std::vector<std::thread> vt;
    for(int i=0;i<100;i++)
    {
        vt.emplace_back([&](){
                cnt.fetch_add(1, std::memory_order_relaxed);
                });
    }
    for(auto &t : vt)
    {
        t.join();
    }
    std::cout<<"relaxed order cur cnt:"<<cnt<<std::endl;

    cnt = 0;
    std::atomic<int*> ptr(nullptr);
    int v;
    std::thread pr1([&](){
            int *p = new int(42);
            v = 1024;
            std::cout<<"y1\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            std::cout<<"y2\n";
            ptr.store(p, std::memory_order_release);
            });

    std::thread con1([&](){
            int* p;
            std::cout<<"x1\n";
            while(!(p=ptr.load(std::memory_order_consume)))
            {
            ;
            }
            std::cout<<"x2\n";
            std::cout<<"p:"<<*p<<std::endl;
            std::cout<<"v:"<<v<<std::endl;
            });

    pr1.join();
    con1.join();
    std::cout<<"relaxed order release&consume cur cnt:"<<cnt<<std::endl;

    std::vector<int> v2;
    std::atomic<int> flag2={0};
    std::thread rel2([&](){
            v2.push_back(42);
            flag2.store(1, std::memory_order_release);
            });
    std::thread acq_rel2([&](){
            int expected = 1;
            while(!flag2.compare_exchange_strong(expected, 2, std::memory_order_acq_rel))
            {
            expected = 1;
            }

            });
    std::thread acq2([&](){
            while(flag2.load(std::memory_order_acquire)<2)
            {
            ;
            }
            std::cout<<v2.at(0)<<std::endl;
            });
    rel2.join();
    acq2.join();
    acq_rel2.join();
    std::cout<<"relaxed order acq&rel cur cnt:"<<cnt<<std::endl;

    std::atomic<int> cnt3 = {0};
    std::vector<std::thread> vt3;
    for(int i=0;i<100;i++)
    {
        vt3.emplace_back([&](){
                cnt3.fetch_add(1, std::memory_order_seq_cst);
                });
    }
    for(auto &t : vt3){
        t.join();
    }
    std::cout<<"relaxed order seq cst cur cnt:"<<cnt3<<std::endl;

    return 0;
}
