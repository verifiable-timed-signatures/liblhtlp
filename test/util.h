/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2020
 * */

#ifndef __LHTLP_TEST__
#define __LHTLP_TEST__

#include <sys/time.h>

static void print_exp_info ( 
		struct timeval *start ,
		struct timeval *end , 
		char* exp_name 
	)
{
	struct timeval diff ;
	uint64_t time ; 
	timersub ( end , start , &diff ) ;
	time = diff.tv_sec * 1000000 + diff.tv_usec ;
	printf ( "Time taken for %s: [%lu] microseconds or [%.3f] seconds \n" ,
			exp_name , time , time / 1000000.0 ) ;
}

#define SUCCESS(test_name) (printf("%s test: Passed\n", test_name))
#define FAILED(test_name) (printf("%s test: Failed\n", test_name))

#endif
