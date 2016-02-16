openssl program

usage:

usage:
1. 程序中用到的包含公钥的服务端证书cacert.pem和服务端私钥文件privkey.pem需要使用如下方式生成：

```
openssl genrsa -out privkey.pem 2048
openssl req -new -x509 -key privkey.pem -out cacert.pem -days 1095
```

2. 编译程序用下列命令：

```
gcc -Wall ssl-client.c -o client -lssl -lcrypto
gcc -Wall ssl-server.c -o server -lssl -lcrypto
```

3. 运行程序用如下命令：

```
./server 8888 3 127.0.0.1 cacert.pem privkey.pem
./client 127.0.0.1 8888
```

