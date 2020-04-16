
#include "md5.h"

static const BYTE	g_pad[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static const WORD	g_abssin[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static const WORD	g_s[4][4] = {
	{ 7, 12, 17, 22 },
	{ 5, 9, 14, 20 },
	{ 4, 11, 16, 23 },
	{ 6, 10, 15, 21 }
};

static const WORD	g_x[64] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
	5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
	0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
};

static WORD			(*const g_op[4])(WORD, WORD, WORD) = {
	ft_f,
	ft_g,
	ft_h,
	ft_i
};

/*
**	4 rounds x 16 operations: a = b + ((a + FGHI(b, c, d) + X[k] + T[i]) <<< s)
*/

static void			ft_update(t_md5_unit *unit)
{
	int		i;
	WORD	f;
	WORD	tmp;

	ft_memcpy(unit->prev_hash, unit->hash, 16);
	i = 0;
	while (i < 64)
	{
		f = g_op[i / 16](unit->hash[1], unit->hash[2], unit->hash[3]);
		tmp = ROTL(
			unit->hash[0] + f + unit->block.word[g_x[i]] + g_abssin[i],
			g_s[i / 16][i % 4]
		);
		unit->hash[0] = unit->hash[1] + tmp;
		tmp = unit->hash[0];
		unit->hash[0] = unit->hash[3];
		unit->hash[3] = unit->hash[2];
		unit->hash[2] = unit->hash[1];
		unit->hash[1] = tmp;
		++i;
	}
	unit->hash[0] += unit->prev_hash[0];
	unit->hash[1] += unit->prev_hash[1];
	unit->hash[2] += unit->prev_hash[2];
	unit->hash[3] += unit->prev_hash[3];
}

static void			ft_append_len(BYTE *block, size_t len)
{
	WORD	*wlen;

	wlen = (WORD *)&len;
	if (!wlen[1])
		*((WORD *)(&(block[56]))) = wlen[0];
	else
		*((size_t *)(&(block[56]))) = len;
}

static void			ft_pad_block(t_md5_unit *unit, const BYTE *msg)
{
	if (unit->left_len < 56)
	{
		ft_memcpy(unit->block.byte, msg, unit->left_len);
		ft_memcpy(
			&(unit->block.byte[unit->left_len]), g_pad, 56 - unit->left_len);
		ft_append_len(unit->block.byte, unit->blen);
		unit->left_len = 64;
	}
	else if (unit->left_len <= 64)
	{
		ft_memcpy(unit->block.byte, msg, unit->left_len);
		ft_memcpy(
			&(unit->block.byte[unit->left_len]), g_pad, 64 - unit->left_len);
		ft_update(unit);
		(unit->left_len == 64)
			? ft_memcpy(unit->block.byte, g_pad, 64)
			: ft_bzero(unit->block.byte, 64);
		ft_append_len(unit->block.byte, unit->blen);
		unit->left_len = 64;
	}
	else
		ft_memcpy(unit->block.byte, msg, 64);
}

static int			ft_process_block(t_md5_unit	*unit, const BYTE *msg, int i)
{
	ft_bzero(unit->block.byte, 64);
	ft_pad_block(unit, &(msg[i * 64]));
	ft_update(unit);
	unit->left_len -= 64;
	if (unit->left_len == 64)
	{
		ft_memcpy(unit->block.byte, g_pad, 64);
		ft_append_len(unit->block.byte, unit->blen);
		ft_update(unit);
		return (0);
	}
	if (!unit->left_len)
		return (0);
	return (1);
}

BYTE				*ft_md5(const BYTE *msg, size_t len)
{
	int			i;
	t_md5_unit	unit;
	BYTE		*res;

	if (!len)
		len = ft_strlen((char *)msg);
	unit.hash[0] = A;
	unit.hash[1] = B;
	unit.hash[2] = C;
	unit.hash[3] = D;
	i = 0;
	unit.left_len = len;
	unit.blen = len * 8;
	while (1)
		if (!ft_process_block(&unit, msg, i++))
			break ;
	res = (BYTE *)ft_smemalloc(16, "ft_md5");
	ft_encode(res, (BYTE *)unit.hash, 4);
	return (res);
}