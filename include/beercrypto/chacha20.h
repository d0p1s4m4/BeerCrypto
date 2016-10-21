/*
 * Copyright (c) 2024, d0p1 <contact@d0p1.eu>
 *
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */
#ifndef BEERCRYPTO_CHACHA20_H
# define BEERCRYPTO_CHACHA20_H 1

# include <stddef.h>
# include <stdint.h>

# define BC_CHACHA20_KEY_BYTES 32
# define BC_CHACHA20_NONCE_BYTES 12
# define BC_CHACHA20_ROUND 10
# define BC_CHACHA20_BLOCK_BYTES 64

typedef uint32_t BCChaCha20State[4][4];

typedef struct bc_chacha20_context {
	BCChaCha20State state;
	uint32_t ctr;
} BCChaCha20Ctx;

void bc_chacha20_init(BCChaCha20Ctx *ctx, const uint8_t *key, const uint32_t ctr,
														const uint8_t *nonce);

void bc_chacha20_block(BCChaCha20Ctx *ctx, uint8_t *out);

void bc_chacha20_encrypt(BCChaCha20Ctx *ctx, uint8_t *in, size_t inlen, uint8_t *out);

# define bc_chacha20_decrypt bc_chacha20_encrypt

#endif /* !BEERCRYPTO_CHACHA20_H */