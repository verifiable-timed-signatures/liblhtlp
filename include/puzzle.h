/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#ifndef __LHP_PUZZLE__
#define __LHP_PUZZLE__

typedef struct LHP_puzzle_t {
	mpz_t u ;
	mpz_t v ;
} LHP_puzzle_t ;

typedef struct LHP_puzzle_sol_t {
	mpz_t s ;
} LHP_puzzle_sol_t ;

void LHP_init_puzzle ( LHP_puzzle_t* puzzle ) ;

void LHP_clear_puzzle ( LHP_puzzle_t* puzzle ) ;

int LHP_puzzle_cmp ( LHP_puzzle_t* a , LHP_puzzle_t* b ) ;

#endif
