CC=gcc
INSTALL=install
RM=rm -f

all: studict

install:
	$(INSTALL) -m755 studict ~/.local/bin/studict

uninstall:
	$(RM) ~/.local/bin/studict

clean:
	$(RM) studict

studict: main.c
	$(CC) -o studict main.c

