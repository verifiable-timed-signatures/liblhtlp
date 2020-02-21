INCLUDE := include
SRC := src
LIBS := lib
EXT_LIBS := -lgmp
BUILD_DIR = build
LHP_TARGET := liblhp

.PHONY: all test clean

TARGET := ${LHP_TARGET}
all: ${TARGET}

_LHP_DEPS = config.h lhp.h params.h puzzle.h util.h config.h
LHP_DEPS = $(patsubst %,$(INCLUDE)/%,$(_LHP_DEPS))

_LHP_OBJ = lhp.o params.o puzzle.o util.o
LHP_OBJ = $(patsubst %,$(BUILD_DIR)/%,$(_LHP_OBJ))

CC=gcc
CFLAGS=-I ${INCLUDE} -L ${LIBS} -g

${BUILD_DIR}/%.o: ${SRC}/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

${LHP_TARGET}: ${LHP_OBJ}
	ar rcs ${LIBS}/${LHP_TARGET}.a $^

clean:
	@rm -rf ${BUILD_DIR}/*
	@rm -rf ${LIBS}/*.a

test: ${TARGET}
	make -C test/
