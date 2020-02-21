INCLUDE := ../include
LIBS := ../lib
EXT_LIBS := -llhp -lgmp -lpbc -lssl -lcrypto 

CC=gcc
CFLAGS=-I ${INCLUDE} -L ${LIBS} ${EXT_LIBS} -g

./%.o: %.c
	$(CC) $^ -o $@ $(CFLAGS)

./%.test: %.o
	./$^

test: lhp_test.test \
	batch_test.test

clean: 
	@rm -rf ./*.o
