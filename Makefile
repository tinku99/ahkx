CC = winegcc
CXX = wineg++
RC = wrc
DIRS	= xdotool
PREFIX?=/usr/local
INSTALLBIN?=$(PREFIX)/bin
INSTALLMAN?=$(PREFIX)/man

CFLAGS?=

DEFAULT_LIBS=-L/usr/X11R6/lib -L/usr/local/lib -lX11 -lXtst
DEFAULT_INC=-I/usr/X11R6/include -I/usr/local/include

LIBS=`pkg-config --libs x11 dl 2> /dev/null || echo "$(DEFAULT_LIBS)"`
INC=`pkg-config --cflags x11 dl 2> /dev/null || echo "$(DEFAULT_INC)"`

CFLAGS+=$(INC)
LDFLAGS+=$(LIBS)

all: ahkx.exe 

install: installprog

installprog: ahkx.exe
	install -m 755 ahkx.exe $(INSTALLBIN)/

deinstall: uninstall
uninstall: 
	rm -f $(INSTALLBIN)/ahkx.exe

clean:
	rm -f *.o ahkx.exe || true

ahkx.exe: ahkx.c
	$(CC) $(CFLAGS) $(LDFLAGS) ahkx.c -o $@

package: test-package-build create-package


create-package: 
	@NAME=ahkx-`date +%Y%m%d`; \
	echo "Creating package: $$NAME"; \
	mkdir $${NAME}; \
	tar -zcf $${NAME}.tar.gz $${NAME}/; \
	rm -rf $${NAME}/

# Make sure the package we're building compiles.
test-package-build: create-package
	@NAME=ahkx.exe-`date +%Y%m%d`; \
	echo "Testing package $$NAME"; \
	tar -zxf $${NAME}.tar.gz; \
	make -C $${NAME} ahkx.exe; \
	rm -rf $${NAME}/
	rm -f $${NAME}.tar.gz

