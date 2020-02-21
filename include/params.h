/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#ifndef __LHP_PARAM__
#define __LHP_PARAM__

#include <gmp.h>

typedef struct LHP_param_t {
	mpz_t T ;
	mpz_t N ;
	mpz_t g ;
	mpz_t h ;
} LHP_param_t ;

void LHP_init_param ( LHP_param_t* ) ;

void LHP_clear_param ( LHP_param_t* ) ;

#endif
