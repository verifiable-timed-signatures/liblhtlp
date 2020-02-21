/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include "gmp.h"

#include "params.h"

void LHP_init_param ( LHP_param_t* param )
{
	mpz_init ( param->N ) ;
	mpz_init ( param->T ) ;
	mpz_init ( param->g ) ;
	mpz_init ( param->h ) ;
}

void LHP_clear_param ( LHP_param_t* param )
{
	mpz_clear ( param->N ) ;
	mpz_clear ( param->T ) ;
	mpz_clear ( param->g ) ;
	mpz_clear ( param->h ) ;
}
