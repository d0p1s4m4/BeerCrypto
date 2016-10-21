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
#include <stddef.h>
#include <stdint.h>
#include <beercrypto/unsafe/arcfour.h>

void
bc_arcfour_init(BCArcfourContext *ctx, const uint8_t *key, size_t length)
{
	int i, j;
	uint8_t c;

	for (i = 0; i < 256; i++)
	{
		ctx->state[i] = i;
	}

	for (i = 0, j = 0; i < 256; i++)
	{
		j = (j + ctx->state[i] + key[i % length]) % 256;
		c = ctx->state[i];
		ctx->state[i] = ctx->state[j];
		ctx->state[j] = c;
	}

	ctx->x = 0;
	ctx->y = 0;
}

uint8_t *
bc_arcfour_encrypt(BCArcfourContext *ctx, const uint8_t *in, size_t length, uint8_t *out)
{
	size_t i;
	uint8_t c;

	if (out == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < length; i++)
	{
		ctx->x = (ctx->x + 1) % 256;
		ctx->y = (ctx->y + ctx->state[ctx->x]) % 256;

		/* swap */
		c = ctx->state[ctx->x];
		ctx->state[ctx->x] = ctx->state[ctx->y];
		ctx->state[ctx->y] = c;

		/* xor */
		c = (ctx->state[ctx->x] + ctx->state[ctx->y]) % 256;
		out[i] = in[i] ^ ctx->state[c];
	}
	return (out);
}
