#include <unistd.h>
#include <stdlib.h>

void hello(void)
{
    printf("bye\n");
}
int main(void)
{
    int ret = 0;
    //ret = execl("/usr/bin/vim", "vi", NULL);
    if (ret ==-1){
        perror("open fail\n");
        exit(0);
    }
    atexit(hello);

    return 0;
}

