CC=gcc
ARCH=  # -m32 for 32-bit
CFLAGS=${ARCH} -Wall -pedantic
LDFLAGS=${ARCH}
LIBS=
SRCS=$(shell find . -maxdepth 1 -name '*.c')
OBJS=${SRCS:.c=.o}
TARGET=${OBJS:.o=}

all:    clean ${TARGET}

${TARGET}:  ${OBJS}
	${CC} ${LDFLAGS} -o ${TARGET} ${OBJS} ${LIBS}

${OBJS}:    ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS}

debug:	clean
debug:	CFLAGS += -DDEBUG -g
debug: 	${TARGET}

.PHONY:	clean
clean:	
	rm -rf *.o ${TARGET}
    
