#ifndef BEERCRYPTO_H
# define BEERCRYPTO_H 1

# include <beercrypto/ripemd160.h>

# ifdef BEERCRYPTO_INCLUDE_UNSAFE
#  include <beercrypto/unsafe/arcfour.h>
#  include <beercrypto/unsafe/misty1.h>
# endif /* !BEERCRYPTO_INCLUDE_UNSAFE */

#endif /* !BEERCRYPTO_H */