/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <d0p1@yahoo.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 		d0p1
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
	uint8_t	*state;
	int	i;
	int	j;
} bc_arcfour_ctx_t;

static inline void bc_byte_swap(uint8_t *a, uint8_t *b)
{
	uint8_t	c;

	c = *a;
	*a = *b;
	*b = c;
}

bc_arcfour_ctx_t	*bc_arcfour_init_ctx(void)
{
	bc_arcfour_ctx_t	*ctx;
	uint16_t		idx;

	ctx = (bc_arcfour_ctx_t *)malloc(sizeof(bc_arcfour_ctx_t));
	if (ctx == NULL)
		return (NULL);
	ctx->state = (uint8_t *)malloc(sizeof(uint8_t) * 256);
	if (ctx == NULL) {
		free(ctx);
		return (NULL);
	}
	for (idx = 0; idx < 256; idx++)
	{
		ctx->state[idx] = idx;
	}
	ctx->i = 0;
	ctx->j = 0;
	return (ctx);
}

void	bc_arcfour_init_key(bc_arcfour_ctx_t *ctx, char const *key, size_t length)
{
	uint16_t idx;

	for (idx = 0; idx < 256; idx++)
	{
		ctx->i = (ctx->i + ctx->state[idx] + key[idx % length]) % 256;
		bc_byte_swap(ctx->state + idx, ctx->state + ctx->i);
	}
	ctx->i = 0;
}

uint8_t	*bc_arcfour_encrypt(bc_arcfour_ctx_t *ctx, uint8_t *data, size_t length)
{
	uint8_t	*result;
	uint8_t	temp;
	size_t	idx;

	result = (uint8_t *)malloc(sizeof(uint8_t) * length);
	for (idx = 0; idx < length; idx++)
	{
		ctx->i = (ctx->i + 1) % 256;
		ctx->j = (ctx->j + ctx->state[ctx->i]) % 256;
		bc_byte_swap(ctx->state + ctx->i, ctx->state + ctx->j);
		temp = ctx->state[(ctx->state[ctx->i] + ctx->state[ctx->j]) % 256];
		result[idx] = data[idx] ^ temp;
	}
	return (result);
}

void	bc_arcfour_destroy(bc_arcfour_ctx_t *ctx)
{
	free(ctx->state);
	free(ctx);
}

int main(void)
{
	uint8_t *byte;
	bc_arcfour_ctx_t *ctx = NULL;

	ctx = bc_arcfour_init_ctx();
	if (ctx == NULL)
		return (-1);
	bc_arcfour_init_key(ctx, "je code avec le cul", 19);
	byte = bc_arcfour_encrypt(ctx, (uint8_t *)"je suis un test\n",16);
	printf("%s\n", byte);
	free(byte);
	bc_arcfour_destroy(ctx);
	return (0);
}
