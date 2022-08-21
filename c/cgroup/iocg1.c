#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main(void)
{
    char cmd[128];

    mkdir("/sys/fs/cgroup/blkio/zz",755);

    // ls -l /dev/sda1 => brw-rw---- 1 root disk 8, 1 Jan 24 09:59 /dev/sda1 => got "8:0"
    system("echo '8:0 1048576'  > /sys/fs/cgroup/blkio/zz/blkio.throttle.read_bps_device");

    sprintf (cmd, "echo %ld >> /sys/fs/cgroup/blkio/zz/tasks " , syscall(SYS_gettid));
    system (cmd);

    system("sudo dd if=/dev/sda1 of=/dev/null");
    return 0;
}




