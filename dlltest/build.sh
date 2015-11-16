rm *.so
rm *.out
rm *.o
export LD_LIBRARY_PATH=$(pwd)	#this add cwd to ld path
gcc -fPIC -shared -olibmy_math.so test_so.c #must name .so to lib***.so,or -l will not find the so
#gcc test_so_main.c ./libmy_math.so -lm		#hardcode the so path
gcc test_so_main.c -L./ -lmy_math -lm -ldl	#cowork with line 4	#use dlfcn.h must add -ldl
