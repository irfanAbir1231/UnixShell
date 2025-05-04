# -*-Makefile-*- UNIXSHELL_OBJDIR := $(USER_OBJDIR)/unixshell OBJDIRS +=
$(UNIXSHELL_OBJDIR) UNIXSHELL_SRCFILES := user/unixshell/unixshell.c
UNIXSHELL_OBJFILES := $(patsubst %.c, $(OBJDIR)/%.o, $(UNIXSHELL_SRCFILES))
UNIXSHELL_OBJFILES := $(patsubst %.S, $(OBJDIR)/%.o, $(UNIXSHELL_OBJFILES))
unixshell: $(UNIXSHELL_OBJFILES) $(USER_LIB) @echo + ld [UNIXSHELL]
$(USER_OBJDIR)/unixshell/unixshell @mkdir -p $(USER_OBJDIR)/unixshell $(V)$(LD)
-o $(USER_OBJDIR)/unixshell/unixshell $(USER_LDFLAGS) $(UNIXSHELL_OBJFILES)
$(USER_LIB) $(V)$(OBJDUMP) -S $(USER_OBJDIR)/unixshell/unixshell >
$(USER_OBJDIR)/unixshell/unixshell.asm $(V)$(NM) -n
$(USER_OBJDIR)/unixshell/unixshell > $(USER_OBJDIR)/unixshell/unixshell.sym
$(OBJDIR)/user/unixshell/%.o: user/unixshell/%.c @echo + cc [UNIXSHELL] $<
@mkdir -p $(@D) $(V)$(CC) $(USER_CFLAGS) -c -o $@ $<
$(OBJDIR)/user/unixshell/%.o: user/unixshell/%.S @echo + as [UNIXSHELL] $<
@mkdir -p $(@D) $(V)$(CC) $(USER_CFLAGS) -c -o $@ $
