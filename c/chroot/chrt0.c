#include <unistd.h>

int main(int argc, char *argv[])
{
#if 0
    //use syscall 
    chroot("/workspace/vagrant/vag0/_install");
    chdir("/");

    char *arrays[]={"ash",NULL};
    execvp("ash", arrays);

#else
    //or use shell cmd
    system("chroot /workspace/vagrant/vag0/_install /bin/ash");
#endif

    return 0;
}
