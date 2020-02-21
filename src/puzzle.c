/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include "gmp.h"

#include "puzzle.h"

void LHP_init_puzzle ( LHP_puzzle_t* puzzle )
{
	mpz_init ( puzzle->u ) ;
	mpz_init ( puzzle->v ) ;
}

void LHP_clear_puzzle ( LHP_puzzle_t* puzzle )
{
	mpz_clear ( puzzle->u ) ;
	mpz_clear ( puzzle->v ) ;
}
