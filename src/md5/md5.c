
#include "md5.h"

/*
**	constants
*/

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

static WORD			g_hash[4] = {
	A, B, C, D
};

/*
**	functions
*/

void				ft_md5_init_e(t_e *e)
{
	e->command_name = ft_strdup("MD5");
	e->update_hash = ft_md5_update;
	e->output_hash = ft_md5_output_hash;
}

void				ft_md5_output_hash(int isendl)
{
	ft_printf(
		"%.8x%.8x%.8x%.8x%s",
		g_hash[0],
		g_hash[1],
		g_hash[2],
		g_hash[3],
		isendl ? "\n" : ""
	);
}

void				ft_md5_encode(void)
{
	int		i;
	BYTE	res[16];

	i = 0;
	while (i < 16)
	{
		res[i] = ((BYTE *)g_hash)[((i / 4 + 1) * 4 - 1) - (i - i / 4 * 4)];
		++i;
	}
	ft_memcpy(g_hash, res, 16);
}

/*
**	4 rounds x 16 operations: a = b + ((a + FGHI(b, c, d) + X[k] + T[i]) <<< s)
*/

void				ft_md5_block_update(WORD *b)
{
	int		i;
	WORD	f;
	WORD	tmp;
	WORD	prev_hash[4];

	ft_memcpy(prev_hash, g_hash, 16);
	i = 0;
	while (i < 64)
	{
		f = g_op[i / 16](g_hash[1], g_hash[2], g_hash[3]);
		tmp = ROTL(
			g_hash[0] + f + b[g_x[i]] + g_abssin[i],
			g_s[i / 16][i % 4]
		);
		g_hash[0] = g_hash[1] + tmp;
		tmp = g_hash[0];
		g_hash[0] = g_hash[3];
		g_hash[3] = g_hash[2];
		g_hash[2] = g_hash[1];
		g_hash[1] = tmp;
		++i;
	}
	g_hash[0] += prev_hash[0];
	g_hash[1] += prev_hash[1];
	g_hash[2] += prev_hash[2];
	g_hash[3] += prev_hash[3];
}

void				ft_md5_update(const BYTE *msg, size_t len, int is_end)
{
	int			i;
	t_oblock	ob;

	i = 0;
	ob.msg = msg;
	if (is_end)
		ob.blen = len * 8;
	ob.left_len = len % SSL_BSIZE;
	while (1)
		if (!ft_process_hash_block(&ob, ft_md5_block_update, i++, is_end))
			break ;
	if (is_end)
		ft_md5_encode();
}
