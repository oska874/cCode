#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc<2){
        printf("Usage: chroot NEWROOT [COMMAND...] \n");
        return 1;
    }

    printf("newroot = %s\n", argv[1]);
    if(chroot(argv[1])) {
        perror("chroot");
        return 1;
    }

    if(chdir("/")) {
        perror("chdir");
        return 1;
    }

    printf("argc %d\n",argc);
    if(argc == 2) {
        argv[0] = getenv("SHELL");
        if(!argv[0])
            argv[0] = (char *)"/bin/sh";

        argv[1] = (char *) "-i";
        argv[2] = NULL;
    } else {
        argv += 2;
    }

    execvp (argv[0], argv);
    printf("chroot: cannot run command `%s`\n", *argv);

    return 0;
}
