#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/syscall.h>
#include <lib/string.h>
#include <user/include/stdio.h>
#include <user/include/proc.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 16
#define HISTORY_SIZE 10

// Shell prompt
#define PROMPT "unix@mcertikos> "

// Command history
char history[HISTORY_SIZE][MAX_COMMAND_LENGTH];
int history_count = 0;
int history_index = 0;

// Forward declarations
void execute_command(char *cmd);
void parse_command(char *cmd, char *argv[]);
void add_to_history(char *cmd);
void display_history(void);

int main(int argc, char **argv) {
    char command[MAX_COMMAND_LENGTH];
    
    printf("mCertiKOS Unix Shell\n");
    printf("Type 'help' for available commands\n");
    
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
        
        // Add command to history
        add_to_history(command);
        
        // Check for exit command
        if (strcmp(command, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }
        
        // Execute command
        execute_command(command);
    }
    
    return 0;
}

// Add command to history
void add_to_history(char *cmd) {
    // Don't add empty commands or duplicates of the last command
    if (cmd[0] == '\0' || (history_count > 0 && strcmp(cmd, history[(history_count - 1) % HISTORY_SIZE]) == 0)) {
        return;
    }
    
    strcpy(history[history_count % HISTORY_SIZE], cmd);
    history_count++;
    history_index = history_count;
}

// Display command history
void display_history(void) {
    int start = (history_count > HISTORY_SIZE) ? (history_count - HISTORY_SIZE) : 0;
    int i;
    
    for (i = start; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i % HISTORY_SIZE]);
    }
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
    
    // Built-in commands
    
    // help command
    if (strcmp(argv[0], "help") == 0) {
        printf("Available commands:\n");
        printf("  help            - Display this help message\n");
        printf("  exit            - Exit the shell\n");
        printf("  clear           - Clear the screen\n");
        printf("  echo [text]     - Display text\n");
        printf("  ps              - List processes\n");
        printf("  history         - Show command history\n");
        printf("  cat [filename]  - Display file contents\n");
        printf("  ls [directory]  - List directory contents\n");
        printf("  cd [directory]  - Change current directory\n");
        printf("  pwd             - Print working directory\n");
        return;
    }
    
    // clear command
    if (strcmp(argv[0], "clear") == 0) {
        // Simple clear - just print newlines
        for (int j = 0; j < 25; j++) {
            printf("\n");
        }
        return;
    }
    
    // echo command
    if (strcmp(argv[0], "echo") == 0) {
        int i = 1;
        while (argv[i] != NULL) {
            printf("%s ", argv[i]);
            i++;
        }
        printf("\n");
        return;
    }
    
    // ps command
    if (strcmp(argv[0], "ps") == 0) {
        printf("PID  STATUS  NAME\n");
        printf("---  ------  ----\n");
        // This would need actual system call support to list processes
        printf("1    READY   init\n");
        printf("%d    RUNNING unixshell\n", sys_getpid());
        return;
    }
    
    // history command
    if (strcmp(argv[0], "history") == 0) {
        display_history();
        return;
    }
    
    // cat command stub
    if (strcmp(argv[0], "cat") == 0) {
        if (argv[1] == NULL) {
            printf("Usage: cat [filename]\n");
        } else {
            printf("File system access not yet implemented\n");
        }
        return;
    }
    
    // ls command stub
    if (strcmp(argv[0], "ls") == 0) {
        printf("File system access not yet implemented\n");
        return;
    }
    
    // cd command stub
    if (strcmp(argv[0], "cd") == 0) {
        printf("Directory navigation not yet implemented\n");
        return;
    }
    
    // pwd command stub
    if (strcmp(argv[0], "pwd") == 0) {
        printf("/\n");
        return;
    }
    
    // Try to execute as a program
    int pid = sys_spawn(argv[0], 0);
    if (pid > 0) {
        // Wait for the program to complete
        sys_wait(pid);
    } else {
        printf("Unknown command: %s\n", argv[0]);
    }
}