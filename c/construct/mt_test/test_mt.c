/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_t ct1,ct2,ct3,ct4;

void *ct_exit (void *arg)
{
    printf("child thread exit\n");
    return 0;
}

//child thread prototype： void *func(void *)

void *child_thread (void *num)
{
    pthread_cleanup_push((void *)ct_exit,NULL);    
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

int pthread_test (void)
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
        exit(-2);
    }
    
    ret = pthread_create(&ct2,NULL,(void *)child_thread,(void *)&num2);
    if (ret){
        perror("create new thread fail ");
        exit(-3);
    }    
    
    ret = pthread_create(&ct3,NULL,(void *)child_thread,(void *)&num3);
    if (ret){
        perror("create new thread fail ");
        exit(-4);
    }  
    
    ret = pthread_create(&ct3,NULL,(void *)child_thread,(void *)&num4);
    if (ret){
        perror("create new thread fail ");
        ret = -5;
        pthread_exit(&ret);
    }  
     
    void *ret1;
    pthread_join(ct3,&ret1);//wait for child 2 thread 
    printf("ct %d\n",*(int *)ret1);    //get child 2 thread return values
    
    printf("tt done\n");
    return 0;
}

//thread synchronization
static int tt2 = 0;
//mutex
pthread_mutex_t tt2_l = PTHREAD_COND_INITIALIZER; //or using pthread_mutex_init()
pthread_rwlock_t rw2_l ;

pthread_cond_t qrdy = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void *cs_thread1 (void *arg)
{
    printf("hello i'm thread 1\n");
    if ((int *)arg == (int *)1) {
        //mutex
        pthread_mutex_lock(&tt2_l);
    }
    else if ((int *)arg == (int *)2) {
	
    }
    tt2 +=100;
    printf("1tt2 %d\n",tt2);
    sleep(1);
    tt2 +=100;
    printf("1tt2 %d\n",tt2);
    if ((int *)arg == (int *)1) {
        //mutex
        pthread_mutex_unlock(&tt2_l);
    }
    
    return (void *)0;
}

void *cs_thread2 (void* arg)
{
    printf("hello i'm thread 2\n");
    if ((int *)arg == (int *)1) {
        //mutex
        pthread_mutex_lock(&tt2_l);
    }
	
    tt2 +=1000;
    printf("2tt2 %d\n",tt2);
    tt2 +=1000;
    printf("2tt2 %d\n",tt2);
    if ((int *)arg == (int *)1) {
	//mutex
	pthread_mutex_unlock(&tt2_l);
    }
    return (void *)0;
}

void *rwlock_test1(void *arg)
{ 
    //rw lock
    if (pthread_rwlock_rdlock(&rw2_l)){
        perror("1 get rd lock fail ");
    }
    
    for(int i=0;i<3;i++) {
        printf("1 tt2 %d\n",tt2);
        sleep(1);
    }
    
    if(pthread_rwlock_unlock(&rw2_l)){
        printf("1 release rd lock fail");
        sleep(1);
    }    
    return (void *)0;
}

void *rwlock_test2(void *arg)
{ 
    //rw lock
    if (pthread_rwlock_rdlock(&rw2_l)){
        perror ("2 get rd lock fail ");
    }
    
    for(int i=0;i<3;i++){
        printf("2 tt2 %d\n",tt2);
        sleep(1);
    }
    
    if(pthread_rwlock_unlock(&rw2_l)){
        printf ("2 release rd lock fail");
    }    
    return (void *)0;
}

void *rwlock_test3(void *arg)
{ 
    //rw lock
    if (pthread_rwlock_wrlock(&rw2_l)){
        perror ("3 get wr lock fail ");
    }
    
    for(int i=0;i<3;i++){
        printf("3 tt2 %d\n",tt2);
        sleep(1);
    }
    
    if(pthread_rwlock_unlock(&rw2_l)){
        printf ("3 release wr lock fail");
    }    
    return (void *)0;
}

void *rwlock_test4(void *arg)
{ 
    //rw lock
    if (pthread_rwlock_wrlock(&rw2_l)){
        perror ("4 get wr lock fail ");
    }
    
    for(int i=0;i<3;i++){
        printf("4 tt2 %d\n",tt2);
        sleep(1);
    }
    
    if(pthread_rwlock_unlock(&rw2_l)){
        printf ("4 release wr lock fail");
    }    
    return (void *)0;
}


//也可以用到多进程同步
int pthread_test2 (void)
{
    int ret;
   
    //mutex
    printf("mutext \n");
    ret = pthread_create(&ct2,NULL,(void *)cs_thread2,(void *)1);
    if (ret){
        perror("create thread1 fail ");
        exit(-2);
    }
      
    ret = pthread_create(&ct1,NULL,(void *)cs_thread1,(void *)1);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
    
    pthread_join(ct1,NULL);
    pthread_join(ct2,NULL);
    
    //rw lock read
    printf("rwlock read\n");
    ret = pthread_rwlock_init(&rw2_l,NULL);
    if (ret){
        perror("rw lock init fail ");
        exit(-2);
    }
    
    ret = pthread_create(&ct2,NULL,(void *)rwlock_test2,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-2);
    }
      
    ret = pthread_create(&ct1,NULL,(void *)rwlock_test1,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
    pthread_join(ct1,NULL);
    pthread_join(ct2,NULL);
    
    //two thread using rw lock write
    printf("rwlock write\n");
    ret = pthread_create(&ct3,NULL,(void *)rwlock_test3,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
    
    ret = pthread_create(&ct4,NULL,(void *)rwlock_test4,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
        
    pthread_join(ct3,NULL);
    pthread_join(ct4,NULL);

    ret = pthread_rwlock_destroy(&rw2_l);
    if (ret){
        perror("rw lock init fail ");
        exit(-3);
    }
    
    printf("tt2 done %d\n",tt2);
    return 0;
}

//同步：条件变量
void *process_msg(void *arg)
{
    //for(;;){
        pthread_mutex_lock(&qlock);
        printf("before process %d\n",tt2);
        while(tt2==0)
            pthread_cond_wait(&qrdy,&qlock);
        printf("process %d\n",tt2);
        tt2 = 0;
        pthread_mutex_unlock(&qlock);
    //}
    return (void*)0;
}
void *produce_msg(void *arg)
{
    printf("enter %s\n",__func__);
    sleep(1);
    pthread_mutex_lock(&qlock);
    tt2=12;
    pthread_mutex_unlock(&qlock);
    printf("resume process\n");
    pthread_cond_signal(&qrdy);
    printf("resume process2\n");
    return (void*)0;
}

int pthread_test3(void)
{
    int ret;
    tt2 = 0;
    printf("rwlock write\n");
    ret = pthread_create(&ct3,NULL,(void *)process_msg,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
    
    ret = pthread_create(&ct4,NULL,(void *)produce_msg,NULL);
    if (ret){
        perror("create thread1 fail ");
        exit(-1);
    }
        
    pthread_join(ct3,NULL);
    pthread_join(ct4,NULL);
    return 0;
}