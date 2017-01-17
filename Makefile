TARGET = password

CC = gcc

COMPILE = $(CC) -c
LINK = $(CC)

CFLAGS = -Wall -std=c11
LFLAGS = -Wall
INCLUD = -Iinclude
LIBRAR = -Llib

SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSDIR = /usr/bin

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*/*.c) 
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))
BINARY  = $(BINDIR)/$(TARGET)

$(BINARY): $(OBJECTS)
	@ test -d $(@D) || mkdir $(@D)
	@echo Building $@
	@$(LINK) $^ -o $@ $(LFLAGS) $(LIBRAR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ test -d $(@D) || mkdir $(@D)
	@echo Compiling $<
	@$(COMPILE) $< -o $@ $(CFLAGS) $(INCLUD)

clean:
	@echo Cleanin up
	@rm -r $(OBJDIR) $(BINDIR)

install: $(BINARY)
	cp $(BINDIR)/$(TARGET) $(INSDIR)

uninstall: $(BINARY)
	rm $(INSDIR)/$(TARGET)

test: $(BINARY)
	$(BINARY) 3 4

error: $(BINARY)
	$(BINARY) 3

help: $(BINARY)
	$(BINARY) -help