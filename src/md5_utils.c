
#include "md5.h"

void	*ft_encode(BYTE *dst, const BYTE *src, size_t words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		dst[i * 4] = src[i * 4 + 3];
		dst[i * 4 + 1] = src[i * 4 + 2];
		dst[i * 4 + 2] = src[i * 4 + 1];
		dst[i * 4 + 3] = src[i * 4];
		++i;
	}
	return (dst);
}

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
