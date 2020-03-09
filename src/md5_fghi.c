
#include "md5.h"

WORD	ft_f(WORD x, WORD y, WORD z)
{
	return ((x & y) | (~x & z));
}

WORD	ft_g(WORD x, WORD y, WORD z)
{
	return ((x & z) | (y & ~z));
}

WORD	ft_h(WORD x, WORD y, WORD z)
{
	return (x ^ y ^ z);
}

WORD	ft_i(WORD x, WORD y, WORD z)
{
	return (y ^ (x | ~z));
}
