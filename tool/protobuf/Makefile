CC=g++
CXXFLAGS= -lprotobuf

all: main

proto:
	protoc -I=$(PWD) --cpp_out=$(PWD) $(PWD)/student.proto

main:proto 	
	$(CC)  main.cc student.pb.cc -o ptest $(CXXFLAGS)

run:ptest
	./ptest

clean:
	rm -rf *.o
	rm *.pb.cc
	rm *.pb.h
	rm ptest


