#ifndef PACKING_H
#define PACKING_H

#include <stdint.h>
#include "params.h"
#include "polyvec.h"

// #define unpack_pk DILITHIUM_NAMESPACE(unpack_pk)
void unpack_pk(uint8_t rho[SEEDBYTES], polyveck *t1, const uint8_t pk[CRYPTO_PUBLICKEYBYTES]);

// #define unpack_sig DILITHIUM_NAMESPACE(unpack_sig)
int unpack_sig(uint8_t c[CTILDEBYTES], polyvecl *z, polyveck *h, const uint8_t sig[CRYPTO_BYTES]);

#endif
