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
BIN = $(BINDIR)/$(TARGET)

LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CFLAGS = -I $(INCDIR) -std=c89 -pedantic -Werror -Wstrict-prototypes -Wmissing-prototypes -Wconversion -Wshadow -Wundef -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wuninitialized -Wfloat-equal -Wbad-function-cast -Wstrict-overflow=5 -march=x86-64 -mtune=generic -pipe
CC = gcc

ifdef DEBUG
  CFLAGS += -O0 -DDEBUG -g -ggdb
endif

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJDIR) $(BINDIR) $(BIN)

doc:
	cd $(DOCDIR) && doxygen Doxyfile && cd ..

man:
	mkdir -p $(MANDIR) && help2man $(BIN) > $(MANPAGE) && gzip $(MANPAGE)

clean:
	rm -rf $(OBJDIR)
distclean: clean
	rm -rf $(DOCDIR)/html $(DOCDIR)/latex $(MANDIR) *.log $(LOGDIR)/*.log $(BINDIR)

run: $(BIN)
	./$(BIN)

.PHONY: all doc man clean distclean run

