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

#define SEC_PARAM 	1024 	// Security Parameter

// Number of puzzles to batch
#define START 		1
#define END 		200

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

/* Timing Statistics */
struct timeval start , end ;

/* Initailization code */
static void INIT ()
{
	LHP_init_puzzle ( &dest_puzzle ) ;
	puzzle_array = malloc ( sizeof ( LHP_puzzle_t ) * n ) ;
}

static void SETUP ()
{
	LHP_init_param ( &param ) ;
	LHP_PSetup ( &param , SEC_PARAM , 1000000 ) ;
}

static void GEN ()
{
	LHP_init_puzzle ( &puzzle ) ;
	LHP_PGen ( &puzzle , &param , str , len ) ;
}

/* Clean up memory */
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

static void BATCH_TEST ()
{
	mpz_t num ;
	mpz_init_set_ui ( num , 0 ) ;
	struct timeval start , end ;
	for( int i = 0 ; i < len ; i++ ) {
		mpz_mul_ui ( num , num , 1 << 8 ) ;
		mpz_add_ui ( num , num , (uint8_t)str[i] ) ;
	}
	for ( int i = 0 ; i < START - END ; i++ ) {
		LHP_init_puzzle ( puzzle_array + i ) ;
		LHP_PGen ( puzzle_array + i , &param , str , len ) ;
	}
	for ( int i = START ; i < END ; i++ ) {
		LHP_PEval ( &param , puzzle_array , i , &dest_puzzle ) ;
	}
	SUCCESS ( "Batch" ) ;
}

int main ( int argc , char* argv[] )
{
	INIT () ;
	SETUP () ;
	GEN () ;
	BATCH_TEST () ;
	CLEAN () ;
	return 0 ;
}
