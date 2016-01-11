/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int exec_shell(void)
{
    int ret;
    ret = system("ls -lath");
    return ret;
}

 
int exec_shell2(void)
{
    printf("exec series functions test\n"); 
    char *const ps_argv[] = {"ps","ax",0}; 
    execv("/bin/ps",ps_argv);
    printf("Done.\n");
    return 0;
}
