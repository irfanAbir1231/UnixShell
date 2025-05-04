/* This is a template for implementing system calls in mCertiKOS.
   You may need to modify this file to match your actual kernel implementation. */

   #include <lib/syscall.h>
   #include <lib/x86.h>
   #include <lib/trap.h>
   #include <user/include/proc.h>
   #include <dev/console.h>
   
   // Add system call numbers here
   #define SYS_getc 2 // Define SYS_getc with an appropriate unique value
   #define SYS_yield 3 // Define SYS_yield with a unique value
   #define SYS_getpid 4 // Define SYS_getpid with a unique value
   #define SYS_kill 5 // Define SYS_kill with a unique value
   #define SYS_wait 6 // Define SYS_wait with a unique value
   
   // System call handler
   int32_t syscall(uint32_t syscallno, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5)
   {
       switch (syscallno) {
       case SYS_puts:
           return (int32_t)sys_puts((char *)a1);
       case SYS_getc:
           return (int32_t)sys_getc();
       case SYS_spawn:
           return (int32_t)sys_spawn((char *)a1, (int)a2);
       case SYS_yield:
           sys_yield();
           return 0;
       case SYS_getpid:
           return (int32_t)sys_getpid();
       case SYS_kill:
           return (int32_t)sys_kill((unsigned int)a1);
       case SYS_wait:
           return (int32_t)sys_wait((unsigned int)a1);
       default:
           return -1;
       }
   }