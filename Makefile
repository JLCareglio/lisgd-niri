PREFIX = /usr
SRC = lisgd.c
OBJ = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror -O2 -march=native -pipe -flto $(shell pkg-config --cflags libinput libudev)
LDFLAGS = -flto -Wl,--as-needed
LIBS = $(shell pkg-config --libs libinput libudev) -lm

ifndef WITHOUT_WAYLAND
CPPFLAGS += -DWITH_WAYLAND
LIBS += -lwayland-client
endif

all: options lisgd

options:
	@echo lisgd build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CPPFLAGS = ${CPPFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "LIBS     = ${LIBS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} ${CPPFLAGS} $<

${OBJ}: config.h

config.h:
	cp config.def.h $@

lisgd: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS} ${LIBS}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f lisgd ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/lisgd

	mkdir -p ${DESTDIR}${PREFIX}/share/man/man1
	cp lisgd.1 ${DESTDIR}${PREFIX}/share/man/man1
	chmod 755 ${DESTDIR}${PREFIX}/share/man/man1

clean:
	rm -f lisgd.o lisgd

.PHONY: all options install clean
