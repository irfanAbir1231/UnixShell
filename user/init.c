#include <lib/gcc.h>
#include <user/include/stdio.h>
#include <lib/string.h>
#include <lib/syscall.h>
#include <user/include/proc.h>

int main(int argc, char **argv)
{
    printf("Init process started.\n");
    
    // Start the Unix shell
    int child_pid = sys_spawn("unixshell", 0);
    if (child_pid > 0) {
        printf("Unix shell started with PID: %d\n", child_pid);
        sys_wait(child_pid);
    } else {
        printf("Failed to start Unix shell.\n");
    }
    
    printf("Init process exiting.\n");
    return 0;
}