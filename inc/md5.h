
#ifndef MD5_H

# define MD5_H

# include "libftprintf.h"

# define CONST_MUL	4294967296

# define A			0x01234567
# define B  		0x89abcdef
# define C			0xfedcba98
# define D			0x76543210

typedef uint32_t	WORD;
typedef struct		s_md5_unit
{
	WORD			hash[4];
	WORD			prev_hash[4];
	WORD			oblock[16];
	WORD			(*op[4])(WORD, WORD, WORD);
}					t_md5_unit;

WORD				ft_f(WORD x, WORD y, WORD z);
WORD				ft_g(WORD x, WORD y, WORD z);
WORD				ft_h(WORD x, WORD y, WORD z);
WORD				ft_i(WORD x, WORD y, WORD z);

#endif
