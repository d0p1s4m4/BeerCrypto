#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <beercrypto/unsafe/misty1.h>

static const uint8_t KEY[BC_MISTY1_KEY_BYTES] = {
	0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
};

static const uint8_t PLAINTEXT1[BC_MISTY1_BLOCK_BYTES] = {
	0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
};

static const uint8_t PLAINTEXT2[BC_MISTY1_BLOCK_BYTES] = {
	0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
};

static const uint8_t CIPHERTEXT1[BC_MISTY1_BLOCK_BYTES] = {
	0x8b, 0x1d, 0xa5, 0xf5, 0x6a, 0xb3, 0xd0, 0x7c
};

static const uint8_t CIPHERTEXT2[BC_MISTY1_BLOCK_BYTES] = {
	0x04, 0xb6, 0x82, 0x40, 0xb1, 0x3b, 0xe9, 0x5d
};

static void
test_encrypt(void **state)
{
	uint8_t out[BC_MISTY1_BLOCK_BYTES];

	BCMISTY1Context ctx;

	bc_MISTY1_init(&ctx, KEY);

	assert_non_null(bc_MISTY1_encrypt_block(&ctx, PLAINTEXT1, BC_MISTY1_BLOCK_BYTES, out));
	assert_memory_equal(CIPHERTEXT1, out, BC_MISTY1_BLOCK_BYTES);

	assert_non_null(bc_MISTY1_encrypt_block(&ctx, PLAINTEXT2, BC_MISTY1_BLOCK_BYTES, out));
	assert_memory_equal(CIPHERTEXT2, out, BC_MISTY1_BLOCK_BYTES);
}

static void
test_decrypt(void **state)
{
	uint8_t out[BC_MISTY1_BLOCK_BYTES];

	BCMISTY1Context ctx;

	bc_MISTY1_init(&ctx, KEY);

	assert_non_null(bc_MISTY1_decrypt_block(&ctx, CIPHERTEXT1, BC_MISTY1_BLOCK_BYTES, out));
	assert_memory_equal(PLAINTEXT1, out, BC_MISTY1_BLOCK_BYTES);

	assert_non_null(bc_MISTY1_decrypt_block(&ctx, CIPHERTEXT2, BC_MISTY1_BLOCK_BYTES, out));
	assert_memory_equal(PLAINTEXT2, out, BC_MISTY1_BLOCK_BYTES);
}

int
main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_encrypt),
		cmocka_unit_test(test_decrypt),
	};
 
	return cmocka_run_group_tests(tests, NULL, NULL);
}