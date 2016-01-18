#include "stdio.h"
#include "stdarg.h"
#include "string.h"    

int vararg(char *msg,...);
int vararg2(int cmd,...);

int main()
{
    char *str="1234";
    printf("%s \n",str);
    strcpy(str,"567");
    printf("1111\n");
    printf("%s \n",str);

	vararg("abc","def","ghia","/0");
    vararg2(1,2);
	return 0;
}

int vararg(char *msg,...)
{
	va_list argp;                   /* 定义保存函数参数的结构 */    
    int argno = 0;                  /* 纪录参数个数 */    
    char *para;                     /* 存放取出的字符串参数 */    
    va_start( argp, msg );    /* argp指向传入的第一个可选参数，    msg是最后一个确定的参数 */
    while (1)   
    {    
        para = va_arg( argp, char *);                 /*    取出当前的参数，类型为char *. */    
        if ( strcmp( para, "/0") == 0 )               /* 采用空串指示参数输入结束 */    
            break;    
        printf("Parameter #%d is: %s\n", argno, para);    
        argno++;    
    }    
    va_end( argp );           
    return 0;
}

int vararg2(int cmd,...)
{
    va_list argp;
    int argno = 0;
    int para;
    va_start(argp,cmd);
    switch(cmd)
    {
        case 0: 
            para = va_arg(argp,int);
            printf("AA:%d  %d \n",cmd,para);
            break;
        case 1:
            para = va_arg(argp,int);
            printf("bb:%d  %d \n",cmd,para);
            break;
        default:
            printf("1111\n");
            break;

    }
    va_end(argp);
    return argno;
}