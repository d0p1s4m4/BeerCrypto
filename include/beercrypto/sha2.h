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
#ifndef BEERCRYPTO_SHA2_H
# define BEERCRYPTO_SHA2_H 1

# include <stdint.h>
# include <stddef.h>

# define BC_SHA224_BYTES 28
# define BC_SHA256_BYTES 32
# define BC_SHA384_BYTES 48
# define BC_SHA512_BYTES 64

typedef struct bc_sha2_context {

} BCSHA2Context;

void bc_sha224(uint8_t *out, const uint8_t *in, size_t len);
void bc_sha256(uint8_t *out, const uint8_t *in, size_t len);

void bc_sha384(uint8_t *out, const uint8_t *in, size_t len);
void bc_sha512(uint8_t *out, const uint8_t *in, size_t len);

#endif /* !BEERCRYPTO_SHA2_H */