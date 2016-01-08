/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mem_test.h
 * Author: zl
 *
 * Created on 2016年1月8日, 下午4:08
 */

#ifndef MEM_TEST_H
#define MEM_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

    int open_mmap();
    int open_anony_mmap();
    int close_mmap();
    void read_mem();
    void write_mem();

#ifdef __cplusplus
}
#endif

#endif /* MEM_TEST_H */

