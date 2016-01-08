/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
int exec_shell(void)
{
    int ret;
    ret = system("ls -lath");
    return ret;
}

