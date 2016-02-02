/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

extern char **environ;

void getenv1(void)
{    
    printf("page %ld\n",sysconf(_SC_PAGESIZE));
    char **ep;
    for(ep=environ;*ep!=NULL;ep++)
        puts(*ep);
}

void uname1()
{
    struct utsname ubuf;
    int ret = uname(&ubuf);
    
    if (ret <0) {
        perror("uname fail:");
        return ;
    }
    
    printf("sysname %s node name %s release %s version %s machine %s\n",
        ubuf.sysname,ubuf.nodename,ubuf.release,ubuf.version,ubuf.machine);
}


int main()
{
    getenv1();    
    putenv("AAA=123");
    printf("AAA  %s\n",getenv("AAA"));
    setenv("BBB","boy",1);
    printf("BBB2 %s\n",getenv("BBB"));
    unsetenv("BBB");
    printf("BBB3 %s\n",getenv("BBB"));
    clearenv();
    uname1();
    return 0;
}