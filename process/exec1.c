#include <unistd.h>

int main(void)
{
    int ret;
    ret = execl("/usr/bin/vim", "vi", NULL);
    if (ret ==-1){
        perror("open fail\n");
        exit(0);
    }

    return 0;
}

