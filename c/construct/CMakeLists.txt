PROJECT(test)                       #projcet name
CMAKE_MINIMUM_REQUIRED(VERSION 2.8) #cmake version

SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -static -O0 -Wall -g -ggdb -std=gnu99 -pthread")  #set debug mode c flags
SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -static -O0 -Wall -std=gnu99 -pthread")         #set release mode c flags
SET(CMAKE_BUILD_TYPE "Release")     #set Debug or Release
SET(CMAKE_SOURCE_DIR $PWD)
MESSAGE(CMAKE_SOURCE_DIR)

ADD_SUBDIRECTORY(file_test)
ADD_SUBDIRECTORY(socket_test)
ADD_SUBDIRECTORY(mem_test)
ADD_SUBDIRECTORY(sys_test)
ADD_SUBDIRECTORY(mp_test)
ADD_SUBDIRECTORY(mt_test)
ADD_SUBDIRECTORY(signal_test)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)    #assigin current dir path to var DIR_SRCS

ADD_EXECUTABLE(RTS ${DIR_SRCS} ) #means source file in DIR_SRCS will be built into a executable file `test`

TARGET_LINK_LIBRARIES(RTS test_file)

#TARGET_LINK_LIBRARIES(RTS tcp_client)
#TARGET_LINK_LIBRARIES(RTS tcp_server)
TARGET_LINK_LIBRARIES(RTS socket_test)

TARGET_LINK_LIBRARIES(RTS test_mem)

TARGET_LINK_LIBRARIES(RTS shell_test)

TARGET_LINK_LIBRARIES(RTS test_mp)

TARGET_LINK_LIBRARIES(RTS test_mtt)

TARGET_LINK_LIBRARIES(RTS test_sig)
