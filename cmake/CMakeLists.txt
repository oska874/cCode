PROJECT(test)                       #projcet name
CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #cmake version

SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -static -O0 -Wall -g -ggdb -std=gnu99")  #set debug mode c flags
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -static -O3 -Wall -std=gnu99")         #set release mode c flags
SET(CMAKE_BUILD_TYPE "Release")     #set Debug or Release
SET(CMAKE_SOURCE_DIR /home/zl/src/t2/cmSDK/EXECC/EXECC_cmake/)

ADD_SUBDIRECTORY(file_test)
ADD_SUBDIRECTORY(socket_test)
ADD_SUBDIRECTORY(mem_test)
ADD_SUBDIRECTORY(sys_test)
ADD_SUBDIRECTORY(mp_test)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)    #assigin current dir path to var DIR_SRCS

ADD_EXECUTABLE(EXECC ${DIR_SRCS} ) #means source file in DIR_SRCS will be built into a executable file `test`

TARGET_LINK_LIBRARIES(EXECC test_file)

TARGET_LINK_LIBRARIES(EXECC tcp_client)
TARGET_LINK_LIBRARIES(EXECC tcp_server)

TARGET_LINK_LIBRARIES(EXECC test_mem)

TARGET_LINK_LIBRARIES(EXECC shell_test)

TARGET_LINK_LIBRARIES(EXECC test_mp)
