
#ifndef SSL_H

# define SSL_H

# include "libftprintf.h"

# include <stdio.h>

# define F_P		0x01
# define F_Q		0x02
# define F_R		0x04
# define F_S		0x08

typedef uint8_t		BYTE;
typedef uint32_t	WORD;

BYTE				*ft_md5(const BYTE *msg, size_t len);

#endif

