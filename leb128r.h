#ifndef ___LEB128R_H
#define ___LEB128R_H

#include <stdint.h>
#include <stddef.h>

_Static_assert(__SIZEOF_POINTER__ == 8, "");

#if __linux__

#else
#error
#endif

static inline      uint8_t* leb128r_encode_u64(uint64_t v,         uint8_t *p) {
    uint64_t l = 0, s = 128; 
    while (++l < 10 && v >= s) v -= s, s <<= 7;
    while (l--) *p++= (l > 0 ? 128 : 0) | (v & 127), v >>= 7;
    return p;
}

static inline      uint8_t* leb128r_encode_i64( int64_t v,         uint8_t *p) {
    return leb128r_encode_u64((v << 1) ^ (v >> 63), p);
}

static inline const uint8_t* leb128r_decode_u64(uint64_t *v, const uint8_t *p) {
    uint64_t s = 0, x = 0, b = 0; *v = 0;
    do s += x, *v |= (uint64_t)(*p & 127) << b, x = 1LU << (b += 7);
        while ((*p++ & 128) && b < 70);
    if (p[-1] & 128) return NULL;
    *v += s;
    return p;
}

static inline const uint8_t* leb128r_decode_i64( int64_t *v, const uint8_t *p) {
    uint64_t u; p = leb128r_decode_u64(&u, p);
    *v = (u >> 1) ^ (-(int64_t)(u & 1));
    return p;
}

#endif
