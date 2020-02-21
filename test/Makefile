INCLUDE := ../include
LIBS := ../lib
EXT_LIBS := -llhp -lgmp -lpbc -lssl -lcrypto 

CC=gcc
CFLAGS=-I ${INCLUDE} -L ${LIBS} ${EXT_LIBS} -g

.PHONY: test clean

./%.o: %.c
	@$(CC) $^ -o $@ $(CFLAGS)

./%.test: %.o
	@echo "-----------------------------"
	@echo "Running `basename $^ .o` Test"
	@echo "-----------------------------"
	@./$^
	@echo "============================="

test: code.test \
	timecode.test \
	batch.test \
	seeded.test

clean: 
	@rm -rf ./*.o
