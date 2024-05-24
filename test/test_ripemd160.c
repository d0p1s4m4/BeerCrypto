#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <beercrypto/ripemd160.h>

static void
test_blank(void **state)
{
    uint8_t hash[RIPEMD160_DIGEST_SIZE];
    uint8_t expected[RIPEMD160_DIGEST_SIZE] = {
        0x9c, 0x11, 0x85, 0xa5, 0xc5, 0xe9, 0xfc,
        0x54, 0x61, 0x28, 0x08, 0x97, 0x7e, 0xe8, 
        0xf5, 0x48, 0xb2, 0x25, 0x8d, 0x31
    };

    ripemd160(hash, "", 0);

    assert_memory_equal(hash, expected, RIPEMD160_DIGEST_SIZE);
}
 
int
main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_blank),
	};
 
	return cmocka_run_group_tests(tests, NULL, NULL);
}