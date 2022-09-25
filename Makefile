CC=gcc
CP=cp
RM=rm -f

all: studict

install:
	$(CP) studict /usr/bin/studict

uninstall:
	$(RM) /usr/bin/studict

clean:
	$(RM) studict

studict: main.c
	$(CC) -o studict main.c

