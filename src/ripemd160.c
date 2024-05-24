#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define ROT_L(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define F1(x, y, z) ((x) ^ (y) ^ (z))
#define F2(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define F3(x, y, z) (((x) | ~(y)) ^ (z))
#define F4(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define F5(x, y, z) ((x) ^ ((y) | ~(z)))

static const uint32_t K[5] = {
  0x00000000, 0x5A827999, 0x6ED9EBA1,
  0x8F1BBCDC, 0xA953FD4E,
};

static const uint32_t K1[5] = {
  0x50a28BE6, 0x5C4DD124, 0x6D703EF3,
  0x7A6D76E9, 0x00000000
};

static const uint8_t R[] = {
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
   7,  4, 13,  1, 10,  6, 15,  3, 12,  0,  9,  5,  2, 14, 11,  8,
   3, 10, 14,  4,  9, 15,  8,  1,  2,  7,  0,  6, 13, 11,  5, 12,
   1,  9, 11, 10,  0,  8, 12,  4, 13,  3,  7, 15, 14,  5,  6,  2,
   4,  0,  5,  9,  7, 12,  2, 10, 14,  1,  3,  8, 11,  6, 15, 13
};

static const uint8_t R1[] = {
    5, 14,  7,  0,  9,  2, 11,  4, 13,  6, 15,  8,  1, 10,  3, 12,
    6, 11,  3,  7,  0, 13,  5, 10, 14, 15,  8, 12,  4,  9,  1,  2,
   15,  5,  1,  3,  7, 14,  6,  9, 11,  8, 12,  2, 10,  0,  4, 13,
    8,  6,  4,  1,  3, 11, 15,  0,  5, 12,  2, 13,  9,  7, 10, 14,
   12, 15, 10,  4,  1,  5,  8,  7,  6,  2, 13, 14,  0,  3,  9, 11
};

static const uint8_t S[] = {
  11, 14, 15, 12,  5,  8,  7,  9, 11, 13, 14, 15,  6,  7,  9,  8,
   7,  6,  8, 13, 11,  9,  7, 15,  7, 12, 15,  9, 11,  7, 13, 12,
  11, 13,  6,  7, 14,  9, 13, 15, 14,  8, 13,  6,  5, 12,  7,  5,
  11, 12, 14, 15, 14, 15,  9,  8,  9, 14,  5,  6,  8,  6,  5, 12,
   9, 15,  5, 11,  6,  8, 13, 12,  5, 12, 13, 14, 11,  8,  5,  6
};

static const uint8_t S1[] = {
   8,  9,  9, 11, 13, 15, 15,  5,  7,  7,  8, 11, 14, 14, 12,  6,
   9, 13, 15,  7, 12,  8,  9, 11,  7,  7, 12,  7,  6, 15, 13, 11,
   9,  7, 15, 11,  8,  6,  6, 14, 12, 13,  5, 14, 13, 13,  7,  5,
  15,  5,  8, 11, 14, 14,  6, 14,  6,  9, 12,  9, 12,  5, 15,  8,
   8,  5, 12,  9, 12,  5, 14,  6,  8, 13,  6,  5, 15, 13, 11, 11
};

static const uint32_t H0 = 0x67452301;
static const uint32_t H1 = 0xEFCDAB89;
static const uint32_t H2 = 0x98BADCFE;
static const uint32_t H3 = 0x10325476;
static const uint32_t H4 = 0xC3D2E1F0;

static inline uint32_t
ripemd160_ff(int n, uint32_t x, uint32_t y, uint32_t z)
{
  switch (n)
    {
    case 1:
      return (F1(x, y, z));
    case 2:
      return (F2(x, y, z));
    case 3:
      return (F3(x, y, z));
    case 4:
      return (F4(x, y, z));
    default:
      return (F5(x, y, z));
    }

  return (0);
}

static inline void
ripemd160_compute_block(uint32_t *state, const uint8_t *in)
{
  size_t idx;
  uint32_t schedule[16];
  uint32_t t;
  uint32_t tt;
  uint32_t a, b, c, d, e;
  uint32_t aa, bb, cc, dd, ee;
  size_t j;

  memset(schedule, 0, 16 * sizeof(uint32_t));
  for (idx = 0; idx < 64; idx++)
    {
      schedule[idx / 4] |= in[idx] << (idx % 4 * 8);
    }

  a = state[0];
  b = state[1];
  c = state[2];
  d = state[3];
  e = state[4];
  aa = state[0];
  bb = state[1];
  cc = state[2];
  dd = state[3];
  ee = state[4];

  for (idx = 0; idx < 80; idx++)
    {
      j = idx / 16;
      t =  ROT_L(a + ripemd160_ff(j + 1, b, c, d) + schedule[R[idx]] + K[j], S[idx]) + e;
      tt = ROT_L(aa + ripemd160_ff(5 - j, bb, cc, dd) + schedule[R1[idx]] + K1[j], S1[idx]) + ee;

      a = e;
      e = d;
      d = ROT_L(c, 10);
      c = b;
      b = t;

      aa = ee;
      ee = dd;
      dd = ROT_L(cc, 10);
      cc = bb;
      bb = tt;
    }

  t = state[1] + c + dd;
  state[1] = state[2] + d + ee;
  state[2] = state[3] + e + aa;
  state[3] = state[4] + a + bb;
  state[4] = state[0] + b + cc;
  state[0] = t;
}

static void
ripemd160_internal(uint32_t *state, uint8_t *in, size_t size)
{
  size_t idx;
  size_t padlen;
  uint8_t padding[64];

  padlen = size << 3;
  for (; size >= 64; size -= 64, in += 64)
    {
      ripemd160_compute_block(state, in);
    }

  memset(padding, 0, 64);
  for (idx = 0; idx < size; idx++)
    {
      padding[idx] = in[idx];
    }
  padding[idx] = 0x80;

  if (size >= 56)
    {
      ripemd160_compute_block(state, padding);
      memset(padding, 0, 64);
    }

  padding[63] = padlen >> 56;
  padding[62] = padlen >> 48;
  padding[61] = padlen >> 40;
  padding[60] = padlen >> 32;
  padding[59] = padlen >> 24;
  padding[58] = padlen >> 16;
  padding[57] = padlen >> 8;
  padding[56] = padlen;

  ripemd160_compute_block(state, padding);
}

void
ripemd160(uint8_t *out, uint8_t *in,  size_t size)
{
  size_t idx;
  uint32_t state[5];

  state[0] = H0;
  state[1] = H1;
  state[2] = H2;
  state[3] = H3;
  state[4] = H4;

  ripemd160_internal(state, in, size);

  for (idx = 0; idx < 20; idx += 4)
    {
      out[idx] = state[idx >> 2];
      out[idx + 1] = (state[idx >> 2] >> 8);
      out[idx + 2] = (state[idx >> 2] >> 16);
      out[idx + 3] = (state[idx >> 2] >> 24);
    }
}
