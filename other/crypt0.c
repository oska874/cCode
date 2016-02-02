/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>

//gcc -lcrypt
void crypt1_test()
{
    char str1[]="helloworld";
    printf("crypt1.0 %s\n",crypt(str1,"ab")); //str1 at most 8bit
    printf("crypt1.1 %s\n",crypt(str1,"cd"));
}

int main()
{
    crypt1_test();
    return 0;
}