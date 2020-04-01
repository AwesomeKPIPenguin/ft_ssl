
#include "md5.h"

/*
**	4 rounds x 16 operations: a = b + ((a + FGHI(b, c, d) + X[k] + T[i]) <<< s)
*/

static void	ft_update(t_md5_unit *unit)
{
	int		i;
	WORD	f;
	WORD	tmp;

	ft_memcpy(unit->prev_hash, unit->hash, 16);
	i = 0;
	while (i < 64)
	{
//		printf("Before loop: a %.8x b %.8x c %.8x d %.8x\n",
//			unit->hash[0], unit->hash[1], unit->hash[2], unit->hash[3]); // <--
		f = g_op[i / 16](unit->hash[1], unit->hash[2], unit->hash[3]);
		tmp = ROTL(unit->hash[0] + f + unit->block.word[g_x[i]] + g_abssin[i], g_s[i / 16][i % 4]);
//		printf("          F: %.8x\n", tmp); // <--
		unit->hash[0] = unit->hash[1] + tmp;
		tmp = unit->hash[0];
		unit->hash[0] = unit->hash[3];
		unit->hash[3] = unit->hash[2];
		unit->hash[2] = unit->hash[1];
		unit->hash[1] = tmp;
		++i;
//		printf(" After loop: a %.8x b %.8x c %.8x d %.8x\n",
//			unit->hash[0], unit->hash[1], unit->hash[2], unit->hash[3]); // <--
	}
	unit->hash[0] += unit->prev_hash[0];
	unit->hash[1] += unit->prev_hash[1];
	unit->hash[2] += unit->prev_hash[2];
	unit->hash[3] += unit->prev_hash[3];
//	printf("     Globals: a %.8x b %.8x c %.8x d %.8x\n",
//		unit->hash[0], unit->hash[1], unit->hash[2], unit->hash[3]); // <--
}

static void	ft_append_len(BYTE *block, size_t len)
{
	WORD	*wlen;

	wlen = (WORD *)&len;
	if (!wlen[1])
		*((WORD *)(&(block[56]))) = wlen[0];
	else
		*((size_t *)(&(block[56]))) = len;
}

static void	ft_pad_block(t_md5_unit *unit, const BYTE *msg)
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

static int	ft_process_block(t_md5_unit	*unit, const BYTE *msg, int i)
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

BYTE		*ft_md5(const BYTE *msg, size_t len)
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
	ft_encode(res, (BYTE *)unit.hash, 16);
	return (res);
}