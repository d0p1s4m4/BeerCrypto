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
#ifndef BEERCRYPTO_UNSAFE_MISTY1_H
# define BEERCRYPTO_UNSAFE_MISTY1_H 1

/**
 * \file misty1.h
 * MISTY1 Encryption Algorithm https://datatracker.ietf.org/doc/rfc2994/
 * \addtogroup unsafe
 * @{
 */
# include <stddef.h>
# include <stdint.h>

/** Key length in bytes */
# define BC_MISTY1_KEY_BYTES 16

# define BC_MISTY1_BLOCK_BYTES 8

typedef struct bc_MISTY1_context {
	uint16_t ekey[32];
} BCMISTY1Context;

/**
 * \param[inout] ctx
 * \param[in] key (key MUST be \ref BC_MISTY1_KEY_BYTES length)
 */
void bc_MISTY1_init(BCMISTY1Context *ctx, const uint8_t *key);

uint8_t	*bc_MISTY1_encrypt_block(BCMISTY1Context *ctx, const uint8_t *in,
								size_t length, uint8_t *out);

uint8_t *bc_MISTY1_decrypt_block(BCMISTY1Context *ctx, const uint8_t *in,
								size_t length, uint8_t *out);

/** @} */

#endif /* !BEERCRYPTO_UNSAFE_MISTY1_H */