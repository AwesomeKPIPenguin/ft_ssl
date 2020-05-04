
#ifndef MD5_H

# define MD5_H

# include "ssl.h"

# define A	0x67452301
# define B  0xefcdab89
# define C	0x98badcfe
# define D	0x10325476

WORD		ft_f(WORD x, WORD y, WORD z);
WORD		ft_g(WORD x, WORD y, WORD z);
WORD		ft_h(WORD x, WORD y, WORD z);
WORD		ft_i(WORD x, WORD y, WORD z);

#endif
