
#ifndef MD5_H

# define MD5_H

# include "ssl.h"

# define A			0x67452301
# define B  		0xefcdab89
# define C			0x98badcfe
# define D			0x10325476

# define ROTL(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))

typedef union		u_block
{
	BYTE			byte[64];
	WORD			word[16];
}					t_block;

typedef struct		s_md5_unit
{
	WORD			hash[4];
	WORD			prev_hash[4];
	t_block			block;
	size_t			left_len;
	size_t			blen;
}					t_md5_unit;

void				*ft_encode(BYTE *dst, const BYTE *src, size_t words);

WORD				ft_f(WORD x, WORD y, WORD z);
WORD				ft_g(WORD x, WORD y, WORD z);
WORD				ft_h(WORD x, WORD y, WORD z);
WORD				ft_i(WORD x, WORD y, WORD z);

#endif
