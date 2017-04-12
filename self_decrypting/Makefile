CC=gcc
CFLAGS=-Wall 
#LIBS=-lgcc_s
TARGET=self_modifying
SRCS=${TARGET}.c
OBJS=${SRCS:.c=.o}


all:  ${TARGET}

${TARGET}:  ${OBJS}
	${CC} -o ${TARGET} ${OBJS} 

${OBJS}:  ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS} 

debug:  CFLAGS += -D __DEBUG__ -g
debug:	${TARGET}

.PHONY: clean
clean:
	rm -rf *.o ${TARGET}


