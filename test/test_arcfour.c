#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <beercrypto/unsafe/arcfour.h>

static void
test_enc_Key_Plaintext(void **state)
{
	uint8_t out[9];
	uint8_t expected[9] = {0xBB, 0xF3, 0x16, 0xE8, 0xD9, 0x40, 0xAF, 0x0A, 0xD3};

	BCArcfourContext ctx;

	bc_arcfour_init(&ctx, (const uint8_t *)"Key", 3);

	bc_arcfour_encrypt(&ctx, (const uint8_t *)"Plaintext", 9, out);

	assert_memory_equal(expected, out, 9);
}

static void
test_enc_Wiki_pedia(void **state)
{
	uint8_t out[5];
	uint8_t expected[5] = {0x10, 0x21, 0xBF, 0x04, 0x20};

	BCArcfourContext ctx;

	bc_arcfour_init(&ctx, (const uint8_t *)"Wiki", 4);

	bc_arcfour_encrypt(&ctx, (const uint8_t *)"pedia", 5, out);

	assert_memory_equal(expected, out, 5);
}

static void
test_dec_Wiki_pedia(void **state)
{
	uint8_t out[5];
	uint8_t in[5] = {0x10, 0x21, 0xBF, 0x04, 0x20};
	uint8_t expected[5] = {'p', 'e', 'd', 'i', 'a'};

	BCArcfourContext ctx;

	bc_arcfour_init(&ctx, (const uint8_t *)"Wiki", 4);
	bc_arcfour_encrypt(&ctx, in, 5, out);

	assert_memory_equal(expected, out, 5);
}
 
int
main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_enc_Key_Plaintext),
		cmocka_unit_test(test_enc_Wiki_pedia),
		cmocka_unit_test(test_dec_Wiki_pedia),
	};
 
	return cmocka_run_group_tests(tests, NULL, NULL);
}