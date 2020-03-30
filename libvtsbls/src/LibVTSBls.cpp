#include <vector>

#include <vtsbls/LibVTSBls.h>

using namespace std ;

namespace LibVtsBls {

void initialize ( unsigned char* randSeed , int size)
{
    // TODO: Deal with randomness
    (void)randSeed ;
    (void)size;
    
    // Initialize all groups
    libff::default_ec_pp::init_public_params() ;
}

vector<Zr> random_field_elems(size_t n) {
    vector<Zr> p(n);
    for (size_t i = 0; i < p.size(); i++) {
        p[i] = Zr::random_element();
    }
    return p;
}

} // end of namespace LibVtsBls