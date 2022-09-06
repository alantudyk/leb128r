#include "leb128r.h"
#include <stdio.h>

#define pf printf

static const uint64_t U[] = {
    1 << 14,
    (1 << 14) + 127,
    ~0LU,
    345635437642,
    65460,
    56,
};

static const  int64_t I[] = {
    0,
    (1 << 13) + 63,
    -((1 << 13) + 64),
    -97701,
    987756545,
    1L << 63
};

int main(void) {
    
    pf("\n"); uint64_t a, b; uint8_t r[10], *p;
    
    for (uint64_t i = 0; i < sizeof(U) / 8; ++i) {
        a = U[i], p = leb128r_encode_u64(a, r);
        pf("e: %20lu %20ld\n", a, p - r);
        p = (void *)leb128r_decode_u64(&b, r); if (a != b) goto e;
        pf("d: %20lu %20ld\n\n", b, p - r);
    }
    
    for (uint64_t i = 0; i < sizeof(I) / 8; ++i) {
        a = I[i], p = leb128r_encode_i64(a, r);
        pf("e: %20ld %20ld\n", a, p - r);
        p = (void *)leb128r_decode_i64(&b, r); if (a != b) goto e;
        pf("d: %20ld %20ld\n\n", b, p - r);
    }
    
    return 0;
    
e:  pf("F*\n"); return 1;

}
