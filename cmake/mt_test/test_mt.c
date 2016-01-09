/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_t ct1,ct2,ct3;

void *ct_exit(void *arg)
{
    printf("child thread exit\n");
    return 0;
}

void *child_thread(void *num)
{
    pthread_cleanup_push(ct_exit,NULL);    
    pthread_t self = pthread_self();
    if (*(int *)num == 2) {// child 2 thread wait for child 1 thread
        printf("wait ct1\n");
        pthread_join(ct1,NULL);
    }
    else if (*(int *)num ==3) {
        pthread_cancel(ct2); //stop child 2 thread
    }
    else if (*(int *)num == 4){
        pthread_detach(pthread_self());
    }
    
    for (int i=0;i<3;i++) {
        printf("hello ,i'm child thread %d id %x\n",*(int *)num,
            (unsigned int )self);    
        sleep(1);
    }
    pthread_cleanup_pop(1);
    int ret = 0;
    pthread_exit((void*)&ret);//return values
}

int pthread_test(void)
{
    pthread_attr_t ct1_attr;
    int ret;
    int num = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    
    ret = pthread_attr_init(&ct1_attr);
    if(ret){
        perror("pthread attr init fail ");
        exit(-1);
    }        
    
    ret = pthread_create(&ct1,&ct1_attr,(void *)child_thread,(void *)&num);
    if (ret){
        perror("create new thread fail ");
        exit(-1);
    }
    
    ret = pthread_create(&ct2,NULL,(void *)child_thread,(void *)&num2);
    if (ret){
        perror("create new thread fail ");
        exit(-1);
    }    
    
    ret = pthread_create(&ct3,NULL,(void *)child_thread,(void *)&num3);
    if (ret){
        perror("create new thread fail ");
        exit(-1);
    }  
    
    ret = pthread_create(&ct3,NULL,(void *)child_thread,(void *)&num4);
    if (ret){
        perror("create new thread fail ");
        exit(-1);
    }  
     
    void *ret1;
    pthread_join(ct3,&ret1);//wait for child 2 thread 
    printf("ct %d\n",*(int *)ret1);    //get child 2 thread return values
    return 0;
}