
#ifndef MD5_H

# define MD5_H

# define A  0x01234567
# define B  0x89abcdef
# define C  0xfedcba98
# define D  0x76543210

# define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
# define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
# define H(x, y, z) ((x) ^ (y) ^ (z))
# define I(x, y, z) ((y) ^ ((x) | (~z)))



#endif
