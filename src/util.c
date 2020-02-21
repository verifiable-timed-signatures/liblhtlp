/*
 * Adithya Bhat <bhat24@purdue.edu>
 * 2019
 * */

#include <stdlib.h>

#include "config.h"
#include "util.h"

void generate_prime ( mpz_t p , uint64_t bit_count )
{
	gmp_randstate_t state;
	gmp_randinit_default( state ) ;
	gmp_randseed_ui ( state , rand() ) ;
	// Create 1 << n-1
	mpz_t p_temp;
	mpz_init2 ( p_temp , bit_count ) ;
	mpz_set_ui ( p_temp , 0 ) ;
	mpz_setbit ( p_temp , bit_count - 1 ) ;
	mpz_urandomb ( p , state , bit_count ) ;
	mpz_ior ( p , p , p_temp ) ; // p is some number with n bits
	mpz_nextprime ( p , p ) ;
	gmp_randclear ( state );
}

void generate_prime_preseeded ( mpz_t p , 
	uint64_t bit_count , 
	gmp_randstate_t* state )
{
	// Create 1 << n-1
	mpz_t p_temp;
	mpz_init2 ( p_temp , bit_count ) ;
	mpz_set_ui ( p_temp , 0 ) ;
	mpz_setbit ( p_temp , bit_count - 1 ) ;
	mpz_urandomb ( p , *state , bit_count ) ;
	mpz_ior ( p , p , p_temp ) ; // p is some number with n bits
	mpz_nextprime ( p , p ) ;
	mpz_clear ( p_temp ) ;
}

/* Strong prime generation code
 *
 * Step 1: Generate p'
 * Step 2: Make sure p' is prime
 * Step 3: Get p = 2p'+1
 * Step 4: Ensure that p is prime
 * */
void generate_strong_prime ( mpz_t p , uint64_t bit_count )
{
	mpz_t p_dash;
	mpz_init2 ( p_dash , bit_count - 1 ) ;
	do {
		generate_prime ( p_dash , bit_count - 1 ) ;
		// p = 2p' + 1
		mpz_mul_ui ( p , p_dash , 2 ) ;
		mpz_add_ui ( p , p , 1 ) ;
	} while ( mpz_probab_prime_p ( p , PRIME_ITERS ) == 0 ) ; /* p is not a prime */
}

/* Strong prime generation code
 *
 * Step 1: Generate p'
 * Step 2: Make sure p' is prime
 * Step 3: Get p = 2p'+1
 * Step 4: Ensure that p is prime
 * */
void generate_strong_prime_preseeded ( mpz_t p , 
	uint64_t bit_count , 
	gmp_randstate_t* state )
{
	mpz_t p_dash;
	mpz_init2 ( p_dash , bit_count - 1 ) ;
	do {
		generate_prime_preseeded ( p_dash , bit_count - 1 , state ) ;
		// p = 2p' + 1
		mpz_mul_ui ( p , p_dash , 2 ) ;
		mpz_add_ui ( p , p , 1 ) ;
	} while ( mpz_probab_prime_p ( p , PRIME_ITERS ) == 0 ) ; /* p is not a prime */
}
/*
 * 1. Generate a random element r of N bits
 * 2. Return if gcd ( r , N ) = 1
 * */
void random_group_element ( mpz_t res , mpz_t N )
{
	gmp_randstate_t state;
	gmp_randinit_default( state ) ;
	gmp_randseed_ui ( state , rand() ) ;
	mpz_t temp;
	mpz_init ( temp ) ;
	while ( 1 ) {
		mpz_urandomm ( res , state , N ) ;
		mpz_gcd ( temp , res , N );
		if ( mpz_cmp_ui ( temp , 1 ) == 0 ) {
			break ;
		}
	}
	gmp_randclear ( state );
	mpz_clear ( temp ) ;
}

void random_group_element_preseeded ( mpz_t res , 
		mpz_t N , 
		gmp_randstate_t* state )
{
	mpz_t temp;
	mpz_init ( temp ) ;
	while ( 1 ) {
		mpz_urandomm ( res , *state , N ) ;
		mpz_gcd ( temp , res , N );
		if ( mpz_cmp_ui ( temp , 1 ) == 0 ) {
			break ;
		}
	}
	mpz_clear ( temp ) ;
}

void totient_n ( mpz_t res , mpz_t p , mpz_t q )
{
	mpz_t temp , temp2 ;
	mpz_init_set ( temp , p ) ;
	mpz_init_set ( temp2 , q ) ;
	// phi(n) = p-1*q-1
	mpz_sub_ui ( temp , p , 1 ); // p-1
	mpz_sub_ui ( temp2 , q , 1 ); // q-1
	mpz_mul ( res , temp , temp2 ) ;
	mpz_clear ( temp ) ;
	mpz_clear ( temp2 ) ;
}
