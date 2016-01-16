#include <stdio.h>
#include <stdlib.h>

#include "include/test_file.h"
#include "include/socket_test.h"
#include "include/mem_test.h"
#include "include/sys_test.h"
#include "include/mp_test.h"
#include "include/mt_test.h"
#include "include/sig_test.h"

int main(int argc,char *argv[])
{
    if (argc != 2){
        printf("usage: xx yy\nyy=0 file test\n=1 tcp server\n=2 tcp client\n"
            "=3 udp server\n=4 udp client\n=5 mem test\n=6 multi process\n"
            "=7 multi thread\n=8 sys/procfs\n=9 share mem(api)\n");
        return 0;
    }
    int method = atoi(argv[1]);
    switch (method) {
    case 0:
        printf("write-read file\n");
        write_file("./testfile");        
        read_file("./testfile");
        break;
    case 1:
        printf("tcp server\n");
        int sret = tcp_server_setup();
        if (!sret)
            tcp_server_work();
        printf("tcp server err %d\n",sret);
        printf("done\n");
        break;
    case 2:
        printf("f tcp client\n");
        int cret = tcp_client_setup();  
        if (!cret)
            tcp_client_work();
        printf("tcp client  err %d\n",cret);
        break;
    case 3:
        printf("udp server\n");
        break;
    case 4:
        printf("udp client\n");
        break;
    case 5:
        printf("mem\n");
        int mret = open_mmap();
        if (!mret){
            read_mem();
            write_mem();
            read_mem();
            close_mmap();
        }
        printf("anonymous map\n");
        mret = open_anony_mmap();
        if (!mret){
            read_mem();
            write_mem();
            read_mem();
            close_mmap();
        }
        break;
    case 6:
        printf("multi process\n");
        printf("test 0\n");
        mp_example0();
        printf("test 1\n");
        mp_example1();
        printf("test 2\n");
        mp_example2();
        printf("test 3\n");
        mp_example3();
        printf("test 4\n");
        mp_example4();
        printf("test 5\n");
        mp_example5();
        break;
    case 7:
        printf("multi thread\n10\n");
        printf("test 0\n");
        pthread_test();//多线程基础
        printf("test 1\n");
        pthread_test2();//互斥量和读写锁
        printf("test 2\n");
        pthread_test3();//条件变量
        break;
    case 8:
        printf("sys test\n");
        printf("shell exec\n");
        printf("test 0\n");
        exec_shell();
        printf("test 1\n");
        exec_shell2();
    case 9:
        printf("sharing memory\n");
        shmem_test();
	break;
    case 10:
	printf("signal\n");
	sig_test1();
	sig_test2();
	sig_test3();
	break;
    default:
	break;            
    }    
    return 0;
}
