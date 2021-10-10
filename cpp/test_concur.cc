#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <chrono>
#include <queue>
#include <condition_variable>

static int v = 1;

void critical_section(int change_v)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    v = change_v;
}

void critical_section2(int cv)
{
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    v = cv;
    std::cout<<"cs2:"<<v<<std::endl;
    lock.unlock();
    lock.lock();
    v+=1;
    std::cout<<"cs2-2:"<<v<<std::endl;
}

int main()
{
    std::thread t1([](){
            std::cout<<"hi 0:"<<v<<std::endl;
//            std::cout<<"hi 1"<<std::endl;
            });
    std::thread t2([](){
            std::cout<<"wo 0:"<<v<<std::endl;
//            std::cout<<"wo 1"<<std::endl;
            });
    std::thread t3([](){
            std::cout<<"ld 0:"<<v<<std::endl;
//            std::cout<<"ld 1"<<std::endl;
            });

    std::thread t4(critical_section, 2),
        t5(critical_section, 3);

    std::thread t6(critical_section2, 14),
        t7(critical_section2, 15);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    std::packaged_task<int()> task([](){
            std::cout<<"pack..."<<std::endl;
            return 7;
            });
    std::future<int> res = task.get_future();
    std::thread(std::move(task)).detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"waiting...";
    res.wait();
    std::cout<<"done."<<std::endl<<"future res is "<<res.get()<<std::endl;


    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;

    auto producer = [&]() {
        for(int i=0;;i++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout<<"producing "<<i<<std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };

    auto consumer = [&] {
        while(true){
            std::unique_lock<std::mutex> lock(mtx);
            while(!notified)
            {
                cv.wait(lock);
            }

            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            lock.lock();
            while(!produced_nums.empty())
            {
                std::cout<<"consuming "<<produced_nums.front()<<std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    std::thread p(producer);
    std::thread cs[2];
    for(int i=0;i<2;i++)
    {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for(int i=0;i<2;i++)
    {
        cs[i].join();
    }

    return 0;
}
