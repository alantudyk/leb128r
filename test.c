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
    
    pf("\n");
    
    for (uint64_t i = 0; i < sizeof(U) / 8; ++i) {
        uint64_t a = U[i], b;
        uint8_t r[10] = {}, *p = leb128r_encode_u64(a, r);
        pf("e: %20lu %20ld\n", a, p - r);
        if ((p = (void *)leb128r_decode_u64(&b, r)) == NULL || a != b) {
            pf("F*\n"); return 1;
        };
        pf("d: %20lu %20ld\n\n", b, p - r);
    }
    
    for (uint64_t i = 0; i < sizeof(I) / 8; ++i) {
        int64_t a = I[i], b;
        uint8_t r[10] = {}, *p = leb128r_encode_i64(a, r);
        pf("e: %20ld %20ld\n", a, p - r);
        if ((p = (void *)leb128r_decode_i64(&b, r)) == NULL || a != b) {
            pf("F*\n"); return 1;
        };
        pf("d: %20ld %20ld\n\n", b, p - r);
    }
    
    return 0;
}
