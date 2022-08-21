#include <stdio.h>

//1. c99 用gcc编译必须打开优化，否则inline不会生成独立汇编代码，结果找不到 foo1 （gcc -std=c99 inline0.c -O2）
//2. default gcc inline0.c -O0 不会内联
//3. c99 和 default 下内联之后编译的汇编不一样：c99不会生成独立的汇编，而直接使用，default 则会生成独立的汇编
//4. extern inline defalut 不会生成独立的代码，但是 c99 会生成
//5. c99 和 default 差别还是挺大的
//inline ,static inline,extern inline

inline void foo2() __attribute__((always_inline)) ;

inline void foo1()
{
    printf("foo1 in inline0\n");
}


inline void foo2() 
{
    printf("foo2 in inline1\n");
}

static inline void foo3() /*默认情况下不会生成独立的汇编代码，除非被当函数指针调用或者自己掉自己*/
{
    printf("foo3 in inline2\n");
}

extern inline void foo4()
{
    printf("foo4 in inline 3\n");
}
	
int main()
{
    foo1();
    foo2();
    foo3();
    foo4();
}
