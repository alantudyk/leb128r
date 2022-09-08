#ifndef ___LEB128R_H
#define ___LEB128R_H

#include <stdint.h>

_Static_assert(__linux__ && __SIZEOF_POINTER__ == 8, "");

static inline      uint8_t* leb128r_encode_u64(uint64_t v,         uint8_t *p) {
    uint64_t l = 1, s = 128;
    for (; v >= s && l < 9; ++l) v -= s, s <<= 7;
    while (--l) *p++ = 128 | (v & 127), v >>= 7;
    *p++ = v;
    return p;
}

static inline      uint8_t* leb128r_encode_i64( int64_t v,         uint8_t *p) {
    return leb128r_encode_u64((v << 1) ^ (v >> 63), p);
}

static inline const uint8_t* leb128r_decode_u64(uint64_t *v, const uint8_t *p) {
    uint64_t s = 0, x = 0, b = 0; *v = 0;
    do s += x, *v |= (uint64_t)(*p & 127) << b, x = 1LU << (b += 7);
        while ((*p++ & 128) && b < 63);
    if (b == 63) {
        *v |= (uint64_t)(p[-1]) << 56;
        /* if (~0LU - *v < s) return NULL; */
    }
    *v += s;
    return p;
}

static inline const uint8_t* leb128r_decode_i64( int64_t *v, const uint8_t *p) {
    uint64_t u; p = leb128r_decode_u64(&u, p);
    *v = (u >> 1) ^ (-(int64_t)(u & 1));
    return p;
}

#endif
