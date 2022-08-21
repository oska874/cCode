#include <iostream>
using namespace std;

//一个没有任何意义的类
class A
{
public:
    A() :a(0){ cout << "A默认构造函数" << endl; }
    A(const  A& rsh){ cout << "A复制构造函数" << endl; }
    ~A(){ cout << "A析构函数" << endl; }
private:
    int  a;
};
int main()
{
        try
        {
            A a ;
            throw a;
        }
        catch (A a)
        {
            ;
        }
    return 0;
}
