/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#include <openssl/sha.h>
#include "lhp.h"
#include "util.h"

void LHP_PSetup ( LHP_param_t* params , // Parameters to fill
	uint64_t lambda , uint64_t T )
{
	mpz_t p , q , temp , temp2 ;
	mpz_init2 ( p , lambda ) ;
	mpz_init2 ( q , lambda ) ;
	mpz_init ( temp ) ;
	mpz_init_set_ui ( temp2 , 2 ) ;
	mpz_set_ui ( params -> T , T ) ;
	generate_strong_prime ( p , lambda / 2 ) ; // Generate p = 2p'+ 1
	generate_strong_prime ( q , lambda / 2 ) ; // Generate q = 2q'+ 1
	/*gmp_printf ( "Generated %d-bit Strong Primes\np: %Zx\nq: %Zx\n" , lambda , p*/
		/*, q ) ;*/
	mpz_mul ( params->N , p , q ) ;
	/*
	 * 1. Generate g = -g^2 mod N
	 * 2. Generate t1 = phi(n)
	 * 3. Compute t2 = 2^T mod (t1/2)
	 * 4. Compute h = g^t2 mod N
	 * */
	random_group_element ( params->g , params->N ) ;
	mpz_powm_ui ( params->g , params->g , 2 , params->N ) ;
	mpz_invert ( params->g , params->g , params->N ) ;
	totient_n ( temp , p , q ) ; // temp has phi(n)
	mpz_div_ui ( temp , temp , 2 ) ;
	mpz_powm ( params->h , temp2 , params->T , temp ) ;
	// Confirm with aravind \|/
	mpz_powm ( params->h , params->g , params->h , params->N ) ;
	mpz_clear ( p ) ;
	mpz_clear ( q ) ;
	mpz_clear ( temp ) ;
	mpz_clear ( temp2 ) ;
}

// The function won't hash anything
// Give the function a hashed string
void LHP_PGen ( LHP_puzzle_t* puzzle , LHP_param_t* pp , unsigned char* str ,
		size_t s_size )
{
	gmp_randstate_t state;
	gmp_randinit_default( state ) ;
	gmp_randseed_ui ( state , rand() ) ;
	mpz_t s ;
	mpz_init_set_ui ( s , 0 ) ;
	for(int i = 0 ; i < s_size ; i++) {
		mpz_mul_ui ( s , s , 1 << 8 ) ;
		mpz_add_ui ( s , s , (uint8_t)str[i] ) ;
	}
	mpz_t r , N2 , temp ;
	mpz_init ( r ) ;
	mpz_init ( N2 ) ;
	mpz_init ( temp ) ;
	mpz_pow_ui ( N2 , pp->N , 2 ) ;
	mpz_urandomm ( r , state , N2 ) ;
	mpz_powm ( puzzle->u , pp->g , r , pp->N ) ;
	mpz_mul ( temp , r , pp->N ) ;
	mpz_powm ( puzzle->v , pp->h , temp , N2 ) ;
	mpz_add_ui ( temp , pp->N , 1 ) ;
	mpz_powm ( temp , temp , s , N2 ) ;
	mpz_mul ( puzzle->v , puzzle->v , temp ) ;
	mpz_mod ( puzzle->v , puzzle->v , N2 ) ;
	mpz_clear ( r ) ;
	mpz_clear ( N2 ) ;
	mpz_clear ( temp ) ;
	gmp_randclear ( state );
}

void LHP_PGen_seeded ( LHP_puzzle_t* puzzle , 
		LHP_param_t* pp , 
		unsigned char* str , size_t s_size , 
		unsigned char* seed, size_t seed_len 
	)
{
	mpz_t seed_mpz ;
	mpz_init ( seed_mpz ) ;
	mpz_import ( seed_mpz , seed_len , 1 , 1 , 0 , 0 , seed ) ;
	gmp_randstate_t state;
	gmp_randinit_default ( state ) ;
	gmp_randseed ( state , seed_mpz ) ;
	mpz_t s ;
	mpz_init_set_ui ( s , 0 ) ;
	for(int i = 0 ; i < s_size ; i++) {
		mpz_mul_ui ( s , s , 1 << 8 ) ;
		mpz_add_ui ( s , s , (uint8_t)str[i] ) ;
	}
	mpz_t r , N2 , temp ;
	mpz_init ( r ) ;
	mpz_init ( N2 ) ;
	mpz_init ( temp ) ;
	mpz_pow_ui ( N2 , pp->N , 2 ) ;
	mpz_urandomm ( r , state , N2 ) ;
	mpz_powm ( puzzle->u , pp->g , r , pp->N ) ;
	mpz_mul ( temp , r , pp->N ) ;
	mpz_powm ( puzzle->v , pp->h , temp , N2 ) ;
	mpz_add_ui ( temp , pp->N , 1 ) ;
	mpz_powm ( temp , temp , s , N2 ) ;
	mpz_mul ( puzzle->v , puzzle->v , temp ) ;
	mpz_mod ( puzzle->v , puzzle->v , N2 ) ;
	mpz_clear ( r ) ;
	mpz_clear ( N2 ) ;
	mpz_clear ( temp ) ;
	gmp_randclear ( state );
}
void LHP_PSolve ( LHP_param_t* pp , LHP_puzzle_t* Z , LHP_puzzle_sol_t* solution )
{
	mpz_t idx , w , N2 ;
	mpz_init_set_ui ( idx , 1 ) ;
	mpz_init_set ( w , Z -> u ) ;
	mpz_init ( solution -> s ) ;
	mpz_init ( N2 ) ;
	mpz_mul ( N2 , pp -> N , pp -> N ) ;
	for ( ; mpz_cmp ( idx , pp -> T ) <= 0 ; mpz_add_ui ( idx , idx , 1 ) ) {
		mpz_mul ( w , w , w ) ; // w = w^2
		mpz_mod ( w , w , pp -> N ) ;
	}
	// Compute s = ((((v)/((w)^N))mod(N^2))-1)/(N)
	// 1. Compute w = w^N mod N^2
	mpz_powm ( w , w , pp -> N , N2 ) ;
	// Compute s = ((v/w) modN^2 - 1)/N
	// 2. Compute w = w^-1 mod N^2
	mpz_invert ( w , w , N2 ) ;
	// Compute s = ((v*w) modN2 - 1)/N
	// 3. Compute w = v*w mod N^2
	mpz_mul ( w , Z -> v , w ) ;
	mpz_mod ( w , w , N2 ) ;
	// Compute s = (w-1)/N
	// 4. Compute w = w -1
	mpz_sub_ui ( w , w , 1 ) ;
	mpz_fdiv_q ( w , w , pp -> N ) ;
	mpz_set ( solution -> s , w ) ;
	mpz_clear ( idx ) ;
	mpz_clear ( w ) ;
	mpz_clear ( N2 ) ;
}

// Setup variable number of arguments
void LHP_PEval ( LHP_param_t* pp , LHP_puzzle_t* puzzle_array , size_t
		num_puzzles , LHP_puzzle_t* dest_puzzle )
{
	mpz_t N2 ;
	mpz_init ( N2 ) ;
	mpz_mul ( N2 , pp -> N , pp -> N ) ;
	mpz_init_set_ui ( dest_puzzle -> u , 1 ) ;
	mpz_init_set_ui ( dest_puzzle -> v , 1 ) ;
	for ( int i = 0 ; i < num_puzzles ; i++ ) {
		// u = u*ui
		mpz_mul ( dest_puzzle -> u , dest_puzzle -> u , puzzle_array [ i ] .u ) ;
		mpz_mod ( dest_puzzle -> u , dest_puzzle -> u , pp -> N ) ;
		// v = v*vi 
		mpz_mul ( dest_puzzle -> v , dest_puzzle -> v , puzzle_array [ i ] .v ) ;
		mpz_mod ( dest_puzzle -> v , dest_puzzle -> v , N2 ) ;
	}
	mpz_clear ( N2 ) ;
}
