/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <gmp.h>

#include "lhp.h"
#include "util.h"

#define SEC_PARAM 1024

// Experimental Parameters
int n = 200 ;
char* str = "111111111111111111111"
	"11111111111111111111111111111"
	"11111111111111111111111111111"
	"111111111111111111111" ;
int len = 100 ;

/* Some variables to declare */
LHP_param_t param ;
LHP_puzzle_t puzzle ;
LHP_puzzle_t *puzzle_array ;
LHP_puzzle_t dest_puzzle ;
LHP_puzzle_sol_t solution ;

/* Initailization code */
static void INIT ()
{
	LHP_init_puzzle ( &dest_puzzle ) ;
	puzzle_array = malloc ( sizeof ( LHP_puzzle_t ) * n ) ;
}

/* Measure time for PSetup */
static void SETUP_TEST ()
{
	LHP_init_param ( &param ) ;
	LHP_PSetup ( &param , SEC_PARAM , 1000000 ) ;
	SUCCESS ( "Setup" ) ;
}

/* Measure time for PGen */
static void GEN_TEST ()
{
	LHP_init_puzzle ( &puzzle ) ;
	LHP_PGen ( &puzzle , &param , str , len ) ;
	SUCCESS ( "Gen" ) ;
}

// Experiment 3 : Measure time for PSolve
static void SOLVE_TEST ()
{
	mpz_init ( solution .s ) ;
	LHP_PSolve ( &param , &puzzle , &solution ) ;
	mpz_t num ;
	mpz_init_set_ui ( num , 0 ) ;
	for( int i = 0 ; i < len ; i++ ) {
		mpz_mul_ui ( num , num , 1 << 8 ) ;
		mpz_add_ui ( num , num , (uint8_t)str[i] ) ;
	}
	if ( mpz_cmp ( num , solution .s ) == 0 ) {
		SUCCESS ( "Solver" ) ;
	}
	else {
		FAILED ( "Solver" ) ;
	}
	mpz_clear (num) ;
}

// Experiment 4 : Measure time for PEval
static void BATCH_TEST ()
{
	// Preparing for Experiment 4
	mpz_t num ;
	mpz_init_set_ui ( num , 0 ) ;
	for( int i = 0 ; i < len ; i++ ) {
		mpz_mul_ui ( num , num , 1 << 8 ) ;
		mpz_add_ui ( num , num , (uint8_t)str[i] ) ;
	}
	LHP_init_puzzle ( &dest_puzzle ) ;
	for ( int i = 0 ; i < n ; i ++ ) {
		LHP_init_puzzle ( puzzle_array + i ) ;
		LHP_PGen ( puzzle_array + i , &param , str, len ) ;
	}
	LHP_PEval ( &param , puzzle_array , n , &dest_puzzle ) ;
	LHP_PSolve ( &param , &dest_puzzle , &solution ) ;
	mpz_mul_ui ( num , num , n ) ;
	if ( mpz_cmp ( num , solution .s ) == 0 ) {
		SUCCESS ( "Batch" ) ;
	}
	else {
		FAILED ( "Batch" ) ;
	}
	mpz_clear (num) ;
}

static void CLEAN ()
{
	for ( int i = 0 ; i < n ; i ++ ) {
		LHP_clear_puzzle ( puzzle_array + i ) ;
	}
	LHP_clear_param ( &param ) ;
	LHP_clear_puzzle ( &puzzle ) ;
	LHP_clear_puzzle ( &dest_puzzle ) ;
	free ( puzzle_array ) ;
}

int main ( int argc , char* argv[] )
{
	INIT ();
	SETUP_TEST ();
	GEN_TEST ();
	SOLVE_TEST ();
	BATCH_TEST ();
	CLEAN (); // Clean up
	return 0 ;
}
