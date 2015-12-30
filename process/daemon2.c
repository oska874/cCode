#include <unistd.h>

int main(void)
{
    daemon(1,1);
    while(1);
    return 0;
}
