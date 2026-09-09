/* aoc_md5.h — MD5 hashing, replaces `import hashlib; hashlib.md5(...)`.
 * Self-contained implementation of RFC 1321 (https://www.rfc-editor.org/rfc/rfc1321),
 * no external dependencies beyond the standard math library.
 *
 * RFC 1321's 64-entry mixing table is computed on first use from the
 * formula the RFC actually gives (T[i] = floor(2^32 * |sin(i)|)) rather
 * than pasted in as pre-computed hex constants — see aoc_md5.c for the
 * full explanation and section references.
 *
 * Because of that, this module needs libm: link with -lm on
 * Linux/macOS (the Makefile already does this). MinGW/MSVC on Windows
 * bundle libm's functions into the standard runtime, so no extra flag
 * is needed there.
 */
#ifndef AOC_MD5_H
#define AOC_MD5_H

#include <stddef.h>

/* Computes the MD5 digest of `data` (n bytes) and writes it as a
 * lowercase 32-character hex string (plus NUL) into out, which must
 * be at least 33 bytes. Mirrors hashlib.md5(s.encode()).hexdigest(). */
void md5_hex(const void *data, size_t n, char out[33]);

#endif /* AOC_MD5_H */
