#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "mymath.h"


void call_method2(void)
{
    void *handle;
    char *err;
    double (*hash)(double);
    handle = dlopen("./libmy_math.so",RTLD_LAZY);
    if(!handle) {
        printf("open fail\n");
        fputs(dlerror(),stderr);
        exit(-1);
    }
    hash=dlsym(handle,"my_sin");
    if((err=dlerror()) != NULL){
        dlclose(handle);
        fputs(err,stderr);
        exit(-2);
    }
    printf("res1 %f \n",(*hash)(360.0));
    dlclose(handle);

}
int main()
{
    call_method2();
    printf("res %f\n",my_sin(360));
    return 0;
}
