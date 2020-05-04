
#ifndef FT_SSL_SHA256_H

# define FT_SSL_SHA256_H

# include "ssl.h"

# define A				0x6a09e667
# define B				0xbb67ae85
# define C				0x3c6ef372
# define D				0xa54ff53a
# define E				0x510e527f
# define F				0x9b05688c
# define G				0x1f83d9ab
# define H				0x5be0cd19

# define S(a, b, c)		((a) ^ (b) ^ (c))
# define CH(a, b, c)	(((a) & (b)) ^ ((~a) & (c)))
# define MAJ(a, b, c)	(((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))

#endif
