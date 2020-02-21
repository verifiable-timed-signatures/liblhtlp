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

int main ( int argc , char* argv[] )
{
	int n = 0 ;
	if ( argc == 2 ) {
		n = atoi ( argv [ 1 ] ) ;
	}
	else {
		n = 200 ;
	}
	// Some variables to declare
	LHP_param_t param ;
	LHP_puzzle_t puzzle ;
	LHP_puzzle_t puzzle_array [ n ] ;
	LHP_puzzle_t dest_puzzle ;
	LHP_puzzle_sol_t solution ;
	LHP_init_puzzle ( &dest_puzzle ) ;
	char* str = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" ;
	int len = 100 ;
	struct timeval start , end ;
	// Experiment 1 : Measure time for PSetup
	gettimeofday ( &start , NULL ) ;
	LHP_init_param ( &param ) ;
	LHP_PSetup ( &param , 1024 , 1000000 ) ;
	gettimeofday ( &end , NULL ) ;
	// End of experiment
	print_exp_info ( &start , &end , "LHP_PSetup" ) ; // Print Info
	// Experiment 2 : Measure time for PGen
	gettimeofday ( &start , NULL ) ;
	LHP_init_puzzle ( &puzzle ) ;
	LHP_PGen ( &puzzle , &param , str , len ) ;
	gettimeofday ( &end , NULL ) ;
	// End of experiment
	print_exp_info ( &start , &end , "LHP_PGen" ) ; // Print Info
	// Experiment 3 : Measure time for PSolve
	gettimeofday ( &start , NULL ) ;
	mpz_init ( solution .s ) ;
	LHP_PSolve ( &param , &puzzle , &solution ) ;
	mpz_t num ;
	mpz_init_set_ui ( num , 0 ) ;
	for( int i = 0 ; i < len ; i++ ) {
		mpz_mul_ui ( num , num , 1 << 8 ) ;
		mpz_add_ui ( num , num , (uint8_t)str[i] ) ;
	}
	gmp_printf ( "Started with: %Zd\n Got: %Zd\n" , num , solution.s ) ;
	gettimeofday ( &end , NULL ) ;
	// End of experiment
	print_exp_info ( &start , &end , "LHP_PSolve" ) ; // Print Info
	// Preparing for Experiment 4
	LHP_init_puzzle ( &dest_puzzle ) ;
	for ( int i = 0 ; i < n ; i ++ ) {
		LHP_init_puzzle ( puzzle_array + i ) ;
		LHP_PGen ( puzzle_array + i , &param , str, len ) ;
	}
	// Experiment 4 : Measure time for PEval
	gettimeofday ( &start , NULL ) ;
	LHP_PEval ( &param , puzzle_array , n , &dest_puzzle ) ;
	gettimeofday ( &end , NULL ) ;
	// End of experiment
	print_exp_info ( &start , &end , "LHP_PEval" ) ; // Print Info
	// Clean up
	LHP_PSolve ( &param , &dest_puzzle , &solution ) ;
	mpz_mul_ui ( num , num , n ) ;
	gmp_printf ( "Started with: %Zd\n Got: %Zd\n" , num , solution.s ) ;
	for ( int i = 0 ; i < n ; i ++ ) {
		LHP_clear_puzzle ( puzzle_array + i ) ;
	}
	LHP_clear_param ( &param ) ;
	LHP_clear_puzzle ( &puzzle ) ;
	LHP_clear_puzzle ( &dest_puzzle ) ;
	return 0 ;
}
