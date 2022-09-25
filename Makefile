CC=gcc
INSTALL=install
RM=rm -f

all: studict

install:
	$(INSTALL) -m755 studict /usr/bin/studict

uninstall:
	$(RM) /usr/bin/studict

clean:
	$(RM) studict

studict: main.c
	$(CC) -o studict main.c

