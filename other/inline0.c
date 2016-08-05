#include <stdio.h>

//用gcc编译必须打开优化，否则inline不会生成独立汇编代码，结果找不到 foo1 （gcc -std=c99 inline0.c -O2）

inline void foo1()
{
    printf("foo1 in inline0\n");
}


int main()
{
    foo1();
}
