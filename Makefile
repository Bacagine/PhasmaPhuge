#
# Makefile
#
# PhasmaPhuge
#
# Written by Gustavo Bacagine
#

TARGET = PhasmaPhuge

INCDIR = include
SRCDIR = src
DOCDIR = doc
MANDIR = man
OBJDIR = obj
BINDIR = bin

MANPAGE = $(MANDIR)/$(TARGET).1

SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))
LDLIBS =
CFLAGS = -I $(INCDIR) -std=c89 -pedantic -Werror -Wstrict-prototypes -Wmissing-prototypes -Wconversion -Wshadow -Wundef -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wuninitialized -Wfloat-equal -Wbad-function-cast -Wstrict-overflow=5 -march=x86-64 -mtune=generic -pipe
CC = gcc

LDFLAGS =

ifdef DEBUG
  CFLAGS += -O0 -DDEBUG -g -ggdb
endif

ifdef _WIN32
  SHELL = /usr/bin/bash
  .SHELLFLAGS = -c

  EXE = .exe

  CFLAGS += -I'C:\Libraries\include' -I'C:\Libraries\include\SDL' -Wno-error=switch-default

  LDLIBS = -lmingw32 -lSDL2main -lSDL2 \
           -lSDL2_image -lSDL2_ttf -lSDL2_mixer
  LDFLAGS += -L'C:\Libraries\lib'
  RUN = ./$(BIN)
endif

ifdef LINUX
  EXE =
  LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
  RUN = ./$(BIN)
endif

BIN = $(BINDIR)/$(TARGET)$(EXE)

$(OBJDIR):
	mkdir -p $(OBJDIR) || exit 1

$(BINDIR):
	mkdir -p $(BINDIR) || exit 1

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS) | $(BINDIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

all: $(BIN)

doc:
	cd $(DOCDIR) && doxygen Doxyfile

man: $(BIN)
ifdef _WIN32
	@echo Manual generation is not supported on Windows.
else
	mkdir -p $(MANDIR) || exit 1
	help2man $(BIN) > $(MANPAGE)
	gzip -f $(MANPAGE)
endif

clean:
	rm -rf $(OBJDIR) || exit 1

distclean: clean
	rm -rf $(BINDIR) || exit 1
	rm -rf $(DOCDIR)/html $(DOCDIR)/latex || exit 1
	rm -rf $(MANDIR) *.log || exit 1

run: $(BIN)
	$(RUN)

.PHONY: all doc man clean distclean run

