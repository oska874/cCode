#include <unistd.h>
#include <stdlib.h>

void hello(void)
{
    printf("bye1\n");
    exit(1);
}
int main(void)
{
    int ret = 0;
    ret = execl("/usr/bin/vim", "vi", NULL);
    if (ret ==-1){
        perror("open fail\n");
        exit(0);
    }
    
    return 0;
}
