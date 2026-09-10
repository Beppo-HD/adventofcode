/* aoc_md5.h — MD5 hashing.
 * Self-contained implementation of RFC 1321 (https://www.rfc-editor.org/rfc/rfc1321),
 * no external dependencies beyond the standard math library.
 */
#ifndef AOC_MD5_H
#define AOC_MD5_H

#include <stddef.h>

/* Computes the MD5 digest of `data` (n bytes) and writes it as a
 * lowercase 32-character hex string (plus NUL) into out. */
void md5_hex(const void *data, size_t n, char out[33]);

#endif /* AOC_MD5_H */
