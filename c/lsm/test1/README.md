1. 来源：http://onestraw.net/linux/lsm-example/


2. usage：
需要在内核源码根目录中的 security 目录下创建 geek ，修改 security 目录下的 Makefile 和 Kconfig 文件,它包含三个文件

```
geek
    geek_lsm.c
    Makefile
    Kconfig
```

修改在 security 目录下的 Makefile ，在 Yama 相应的条目下添加对应的项

```
subdir-$(CONFIG_SECURITY_GEEK)     += geek
obj-$(CONFIG_SECURITY_GEEK)        += geek/built-in.o
```

修改在 security 目录下的 Kconifg ，在 Yama 相应的条目下添加对应的项

```
source security/geek/Kconfig
default DEFAULT_SECURITY_GEEK if SECURITY_GEEK
config DEFAULT_SECURITY_GEEK
     bool "Geek" if SECURITY_GEEK=y
default "geek" if DEFAULT_SECURITY_GEEK
```

最后编译内核，`make menuconfig` 时添加上 GEEK 模块，编译后重启就成功加载了 geek 模块。

```
  onestraw@ubuntu:~$ dmesg |tail -10
  [   52.407228] [+geek] call task_create(). count=2799
  [   52.412253] [+geek] call task_create(). count=2800
```
