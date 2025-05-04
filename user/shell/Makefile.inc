# -*-Makefile-*- SHELL_OBJDIR := $(USER_OBJDIR)/shell OBJDIRS += $(SHELL_OBJDIR)
SHELL_SRCFILES := user/shell/shell.c SHELL_OBJFILES := $(patsubst %.c,
$(OBJDIR)/%.o, $(SHELL_SRCFILES)) SHELL_OBJFILES := $(patsubst %.S,
$(OBJDIR)/%.o, $(SHELL_OBJFILES)) shell: $(SHELL_OBJFILES) $(USER_LIB) @echo +
ld [SHELL] $(USER_OBJDIR)/shell/shell @mkdir -p $(USER_OBJDIR)/shell $(V)$(LD)
-o $(USER_OBJDIR)/shell/shell $(USER_LDFLAGS) $(SHELL_OBJFILES) $(USER_LIB)
$(V)$(OBJDUMP) -S $(USER_OBJDIR)/shell/shell > $(USER_OBJDIR)/shell/shell.asm
$(V)$(NM) -n $(USER_OBJDIR)/shell/shell > $(USER_OBJDIR)/shell/shell.sym
$(OBJDIR)/user/shell/%.o: user/shell/%.c @echo + cc [SHELL] $< @mkdir -p $(@D)
$(V)$(CC) $(USER_CFLAGS) -c -o $@ $< $(OBJDIR)/user/shell/%.o: user/shell/%.S
@echo + as [SHELL] $< @mkdir -p $(@D) $(V)$(CC) $(USER_CFLAGS) -c -o $@ $
