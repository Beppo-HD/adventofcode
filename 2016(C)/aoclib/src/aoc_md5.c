/* aoc_md5.c — MD5 (RFC 1321). One-shot hasher
 */
#include "aoc_md5.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/* The initial buffer state of (A,B,C,D) are the Bytewise hex digits 0-f counted
 * up then down: A: 01234567, B: 89abcdef, C: fedcba98, D: 76543210.
 * The words below are that pattern read back little-endian. A fixed,
 * memorable starting point — not cryptographically significant. */
static const uint32_t INITIAL_STATE[4] = {
    0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
};

/* Per-round left-rotation amounts, 4 per round. Tuned by the algorithm's
 * designer to speed up avalanche effect. */
static const int SHIFT[4][4] = {
    { 7, 12, 17, 22 },
    { 5,  9, 14, 20 },
    { 4, 11, 16, 23 },
    { 6, 10, 15, 21 }
};

/* Mixing table T[i] = floor(2^32 * |sin(i)|), i = 1..64 radians
 * Built once with the first computed hash, and reused after that. */
static uint32_t sine_table[64];
static bool sine_table_ready = false;

static void build_sine_table(void) {
    for (int i = 0; i < 64; i++) {
        sine_table[i] = (uint32_t)(4294967296.0 * fabs(sin((double)(i + 1))));
    }
    sine_table_ready = true;
}

static uint32_t rotl32(uint32_t x, int c) {
    return (x << c) | (x >> (32 - c));
}

/* Pad to a multiple of 64 bytes: one 0x80 byte, zeros up to 56 (mod 64),
 * then the original bit-length as an 8-byte little-endian tail. Caller
 * frees the returned buffer. */
static unsigned char *pad_message(const void *data, size_t len, size_t *out_len) {
    size_t padded_len = ((len + 8) / 64 + 1) * 64;
    unsigned char *buf = calloc(1, padded_len);
    memcpy(buf, data, len);
    buf[len] = 0x80;

    uint64_t bitlen = (uint64_t)len * 8;
    for (int i = 0; i < 8; i++) {
        buf[padded_len - 8 + i] = (unsigned char)((bitlen >> (8 * i)) & 0xFF);
    }

    *out_len = padded_len;
    return buf;
}

/* Mixes one 64-byte block into state[0..3] (A,B,C,D) over 64 rounds in
 * 4 groups of 16, each group using a different nonlinear function
 * (F/G/H/I) and a different rule for which message word to mix in
 * (`g`); the round-2/3 word orders were deliberately chosen to look
 * unlike each other. */
static void md5_transform(uint32_t state[4], const unsigned char block[64]) {
    uint32_t M[16];
    for (int i = 0; i < 16; i++) {
        M[i] = (uint32_t)block[i*4]
             | ((uint32_t)block[i*4+1] << 8)
             | ((uint32_t)block[i*4+2] << 16)
             | ((uint32_t)block[i*4+3] << 24);
    }

    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];

    for (int i = 0; i < 64; i++) {
        uint32_t f;
        int g;
        if (i < 16) {
            f = (b & c) | (~b & d);           /* F: bitwise "if b then c else d" */
            g = i;
        } else if (i < 32) {
            f = (d & b) | (~d & c);           /* G */
            g = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = b ^ c ^ d;                    /* H: parity */
            g = (3 * i + 5) % 16;
        } else {
            f = c ^ (b | ~d);                 /* I */
            g = (7 * i) % 16;
        }

        int shift = SHIFT[i / 16][i % 4];

        uint32_t tmp = d;
        d = c;
        c = b;
        b = b + rotl32(a + f + sine_table[i] + M[g], shift);
        a = tmp;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void md5_hex(const void *data, size_t n, char out[33]) {
    if (!sine_table_ready) build_sine_table();

    uint32_t state[4];
    memcpy(state, INITIAL_STATE, sizeof(state));

    size_t padded_len;
    unsigned char *padded = pad_message(data, n, &padded_len);

    for (size_t offset = 0; offset < padded_len; offset += 64) {
        md5_transform(state, padded + offset);
    }
    free(padded);

    /* Digest bytes are the state words, little-endian. */
    unsigned char digest[16];
    for (int i = 0; i < 4; i++) {
        digest[i*4 + 0] = (unsigned char)(state[i] & 0xFF);
        digest[i*4 + 1] = (unsigned char)((state[i] >> 8) & 0xFF);
        digest[i*4 + 2] = (unsigned char)((state[i] >> 16) & 0xFF);
        digest[i*4 + 3] = (unsigned char)((state[i] >> 24) & 0xFF);
    }

    static const char hex_digits[] = "0123456789abcdef";
    for (int i = 0; i < 16; i++) {
        out[i*2]     = hex_digits[(digest[i] >> 4) & 0xF];
        out[i*2 + 1] = hex_digits[digest[i] & 0xF];
    }
    out[32] = '\0';
}
