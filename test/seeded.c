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
char *seed = "00000000000000000000"
	"00000000000000000000000000000"
	"00000000000000000000000000000"
	"0000000000000000000000" ;
int seedlen = 100 ;

/* Some variables to declare */
LHP_param_t param ;
LHP_puzzle_t puzzle , puzzle2 ;

/* Initailization code */
static void INIT ()
{
	LHP_init_puzzle ( &puzzle ) ;
	LHP_init_puzzle ( &puzzle2 ) ;
}

/* Measure time for PSetup */
static void SETUP ()
{
	LHP_init_param ( &param ) ;
	LHP_PSetup ( &param , SEC_PARAM , 1000000 ) ;
	SUCCESS ( "Setup" ) ;
}

/* Measure time for PGen */
static void GEN_TEST ()
{
	LHP_PGen_seeded ( &puzzle , &param , str , len , seed , seedlen ) ;
	LHP_PGen_seeded ( &puzzle2 , &param , str , len , seed , seedlen ) ;
	if ( LHP_puzzle_cmp ( &puzzle , &puzzle2 ) == 0 ) {
		SUCCESS ( "Deterministic Gen" ) ;
	}
	else {
		FAILED ( "Deterministic Gen" ) ;
	}
}

static void CLEAN ()
{
	LHP_clear_param ( &param ) ;
	LHP_clear_puzzle ( &puzzle ) ;
	LHP_clear_puzzle ( &puzzle2 ) ;
}

int main ( int argc , char* argv[] )
{
	INIT ();
	SETUP ();
	GEN_TEST ();
	CLEAN (); // Clean up
	return 0 ;
}
