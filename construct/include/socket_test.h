/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   socket_test.h
 * Author: zl
 *
 * Created on 2016年1月8日, 下午2:05
 */

#ifndef SOCKET_TEST_H
#define SOCKET_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

    int tcp_client_setup();
    int tcp_server_setup();
    int tcp_client_work();
    int tcp_server_work();



#ifdef __cplusplus
}
#endif

#endif /* SOCKET_TEST_H */

