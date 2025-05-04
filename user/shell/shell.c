#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/syscall.h>
#include <lib/string.h>
#include <user/include/stdio.h>
#include <user/include/proc.h>

// Basic shell implementation for mCertiKOS
// This is a simple shell that can be used as a fallback

int main(int argc, char **argv) {
    printf("mCertiKOS Basic Shell\n");
    printf("This is a minimal shell. Please use unixshell for more features.\n");
    printf("Type 'exit' to exit.\n");
    
    char command[256];
    
    while (1) {
        printf("shell> ");
        
        // Get command
        int i = 0;
        while (i < 255) {
            char c = getchar();
            if (c == '\n' || c == '\r') {
                command[i] = '\0';
                break;
            } else if (c >= ' ' && c <= '~') {
                command[i++] = c;
                putchar(c);
            }
        }
        putchar('\n');
        
        // Check for exit
        if (strcmp(command, "exit") == 0) {
            break;
        }
        
        // Echo command
        printf("You entered: %s\n", command);
    }
    
    return 0;
}