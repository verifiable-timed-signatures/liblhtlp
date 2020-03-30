#pragma once

#include <libff/algebra/curves/public_params.hpp>
#include <libff/common/default_types/ec_pp.hpp>

using namespace std ;

namespace LibVtsBls {

// Type of the first group G1
using G1 = typename libff::default_ec_pp::G1_type ;
// Type of second group G2
using G2 = typename libff::default_ec_pp::G2_type ;
// Type of target group GT
using GT = typename libff::default_ec_pp::GT_type ;
// Zr: The field containing the exponents of the EC groups
using Zr = typename libff::default_ec_pp::Fp_type ;

/*
 * Initialize the library with randomness and statistical 
   security parameters
 */

void initialize ( unsigned char* randSeed , int size = 0);

/*
 * Given any group, generate n random elements from that group
 */
template<class G>
vector<G> random_group_elements (size_t n)
{
    vector<G> bases ;
    for(size_t i=0; i<n;i++) {
        bases .push_back ( G::random_element());
    }
    return bases;
}

/*
 * Generate n random elements from Zr
 */
vector<Zr> random_field_elems (size_t n) ;

} // end of libvtsbls namespace