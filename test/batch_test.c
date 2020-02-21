/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <gmp.h>

#include "lhp.h"

void print_exp_info ( struct timeval *start , struct timeval *end , char* exp_name )
{
	struct timeval diff ;
	uint64_t time ; 
	timersub ( end , start , &diff ) ;
	time = diff.tv_sec * 1000000 + diff.tv_usec ;
	printf ( "Time taken for %s: [%lu] microseconds or [%.3f] seconds \n" ,
			exp_name , time , time / 1000000.0 ) ;
}

int START = 1 ;
int END = 200 ;

int main ( int argc , char* argv[] )
{
	// Some variables to declare
	LHP_param_t param ;
	LHP_puzzle_t puzzle [ END - START ];
	LHP_puzzle_t dest_puzzle ;
	LHP_puzzle_sol_t solution ;
	char* str = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" ;
	int len = 100 ;
	LHP_init_param ( &param ) ;
	LHP_init_puzzle ( &dest_puzzle ) ;
	LHP_PSetup ( &param , 1024 , 1000000 ) ;
	mpz_t num ;
	mpz_init_set_ui ( num , 0 ) ;
	struct timeval start , end ;
	for( int i = 0 ; i < len ; i++ ) {
		mpz_mul_ui ( num , num , 1 << 8 ) ;
		mpz_add_ui ( num , num , (uint8_t)str[i] ) ;
	}
	for ( int i = 0 ; i < START - END ; i++ ) {
		LHP_init_puzzle ( puzzle + i ) ;
		LHP_PGen ( puzzle + i , &param , str , len ) ;
	}
	// Preparing for Experiment 4
	// Experiment 4 : Measure time for PEval
	for ( int i = START ; i < END ; i++ ) {
		gettimeofday ( &start , NULL ) ;
		LHP_PEval ( &param , puzzle , i , &dest_puzzle ) ;
		gettimeofday ( &end , NULL ) ;
		printf ( "Iteration - %d\n" , i ) ;
		print_exp_info ( &start , &end , "LHP_PEval" ) ; // Print Info
	}
	// End of experiment
	LHP_clear_param ( &param ) ;
	LHP_clear_puzzle ( &dest_puzzle ) ;
	return 0 ;
}
