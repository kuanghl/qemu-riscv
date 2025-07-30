#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"

typedef struct {
  int32_t coeffs[N];
} poly;

// #define poly_reduce DILITHIUM_NAMESPACE(poly_reduce)
void poly_reduce(poly *a);
// #define poly_caddq DILITHIUM_NAMESPACE(poly_caddq)
void poly_caddq(poly *a);

// #define poly_add DILITHIUM_NAMESPACE(poly_add)
void poly_add(poly *c, const poly *a, const poly *b);
// #define poly_sub DILITHIUM_NAMESPACE(poly_sub)
void poly_sub(poly *c, const poly *a, const poly *b);
// #define poly_shiftl DILITHIUM_NAMESPACE(poly_shiftl)
void poly_shiftl(poly *a);

// #define poly_ntt DILITHIUM_NAMESPACE(poly_ntt)
void poly_ntt(poly *a);
// #define poly_invntt_tomont DILITHIUM_NAMESPACE(poly_invntt_tomont)
void poly_invntt_tomont(poly *a);
// #define poly_pointwise_montgomery DILITHIUM_NAMESPACE(poly_pointwise_montgomery)
void poly_pointwise_montgomery(poly *c, const poly *a, const poly *b);


// #define poly_use_hint DILITHIUM_NAMESPACE(poly_use_hint)
void poly_use_hint(poly *b, const poly *a, const poly *h);

// #define poly_chknorm DILITHIUM_NAMESPACE(poly_chknorm)
int poly_chknorm(const poly *a, int32_t B);
// #define poly_uniform DILITHIUM_NAMESPACE(poly_uniform)
void poly_uniform(poly *a,
                  const uint8_t seed[SEEDBYTES],
                  uint16_t nonce);

// #define poly_challenge DILITHIUM_NAMESPACE(poly_challenge)
void poly_challenge(poly *c, const uint8_t seed[CTILDEBYTES]);


// #define polyt1_unpack DILITHIUM_NAMESPACE(polyt1_unpack)
void polyt1_unpack(poly *r, const uint8_t *a);


// #define polyz_unpack DILITHIUM_NAMESPACE(polyz_unpack)
void polyz_unpack(poly *r, const uint8_t *a);

// #define polyw1_pack DILITHIUM_NAMESPACE(polyw1_pack)
void polyw1_pack(uint8_t *r, const poly *a);

#endif
