#ifndef BEERCRYPTO_RIPEMD160_H
# define BEERCRYPTO_RIPEMD160_H 1

# include <stddef.h>
# include <stdint.h>

# define RIPEMD160_BLOCK_SIZE  64
# define RIPEMD160_DIGEST_SIZE 20

void ripemd160(uint8_t *out, uint8_t *in,  size_t size);

#endif /* !BEERCRYPTO_RIPEMD160_H */
