#ifndef _SHELL_H_
#define _SHELL_H_

#include <lib/gcc.h>
#include <lib/x86.h>
#include <lib/syscall.h>
#include <lib/string.h>
#include <user/include/stdio.h>
#include <user/include/proc.h>

// Shell command constants
#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 16
#define HISTORY_SIZE 10

// Shell prompt
#define PROMPT "unix@mcertikos> "

// Function declarations
void execute_command(char *cmd);
void parse_command(char *cmd, char *argv[]);
void add_to_history(char *cmd);
void display_history(void);

#endif /* _SHELL_H_ */