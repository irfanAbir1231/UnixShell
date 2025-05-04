// user/shell.c
#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 16

// Shell prompt
#define PROMPT "msh> "

// Forward declarations
void execute_command(char *cmd);
void parse_command(char *cmd, char *argv[]);

int main(int argc, char **argv) {
    char command[MAX_COMMAND_LENGTH];
    
    printf("mCertiKOS Shell (msh) - Type 'help' for commands\n");
    
    while (1) {
        // Display prompt
        printf(PROMPT);
        
        // Get command from user
        int i = 0;
        while (i < MAX_COMMAND_LENGTH - 1) {
            char c = getchar();
            if (c == '\n' || c == '\r') {
                command[i] = '\0';
                break;
            } else if (c == '\b' && i > 0) {
                i--;
                // Handle backspace (optional)
                printf("\b \b");
            } else if (c >= ' ' && c <= '~') {
                command[i++] = c;
                putchar(c);
            }
        }
        putchar('\n');
        
        // Handle empty commands
        if (command[0] == '\0') {
            continue;
        }
        
        // Check for exit command
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }
        
        // Handle help command
        if (strcmp(command, "help") == 0) {
            printf("Available commands:\n");
            printf("  help - Display this help message\n");
            printf("  exit - Exit the shell\n");
            printf("  clear - Clear the screen\n");
            printf("  echo [text] - Display text\n");
            printf("  ps - List processes\n");
            continue;
        }
        
        // Handle clear command
        if (strcmp(command, "clear") == 0) {
            // Simple clear - just print newlines
            for (int j = 0; j < 25; j++) {
                printf("\n");
            }
            continue;
        }
        
        // Execute command
        execute_command(command);
    }
    
    return 0;
}

// Parse command into arguments
void parse_command(char *cmd, char *argv[]) {
    int argc = 0;
    char *token = cmd;
    char *end;
    
    // Parse command into arguments
    while (argc < MAX_ARGS - 1) {
        // Skip leading spaces
        while (*token == ' ') token++;
        
        // End of command
        if (*token == '\0') break;
        
        // Find end of current argument
        end = token;
        while (*end != ' ' && *end != '\0') end++;
        
        // Null-terminate this argument
        if (*end == ' ') {
            *end = '\0';
            end++;
        }
        
        // Add to argument list
        argv[argc++] = token;
        
        // Move to next argument
        token = end;
    }
    
    // Null-terminate the argument list
    argv[argc] = NULL;
}

// Execute a command
void execute_command(char *cmd) {
    char *argv[MAX_ARGS];
    
    // Parse command
    parse_command(cmd, argv);
    
    // No arguments
    if (argv[0] == NULL) return;
    
    // Handle echo command
    if (strcmp(argv[0], "echo") == 0) {
        int i = 1;
        while (argv[i] != NULL) {
            printf("%s ", argv[i]);
            i++;
        }
        printf("\n");
        return;
    }
    
    // Handle ps command
    if (strcmp(argv[0], "ps") == 0) {
        printf("PID  STATUS  NAME\n");
        printf("---  ------  ----\n");
        // This would need actual system call support to list processes
        printf("1    READY   init\n");
        printf("%d    RUNNING shell\n", sys_getpid());
        return;
    }
    
    // Unknown command
    printf("Unknown command: %s\n", argv[0]);
}