//Name:Siri Nandipaty student id:21449384
CC = gcc
CFLAGS = -Wall -Werror -g

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))

EXECUTABLE = $(BINDIR)/myshell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)
