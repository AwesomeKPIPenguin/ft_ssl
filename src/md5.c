
#include "md5.h"

void		ft_init_unit(t_md5_unit *unit)
{
	unit->hash[0] = A;
	unit->hash[1] = B;
	unit->hash[2] = C;
	unit->hash[3] = D;
}

static void	ft_turn_words(t_md5_unit *unit)
{
	WORD	tmp;

	tmp = unit->hash[0];
	unit->hash[0] = unit->hash[3];
	unit->hash[3] = unit->hash[2];
	unit->hash[2] = unit->hash[1];
	unit->hash[1] = tmp;
}

/*
**	4 rounds x 16 operations: a = b + ((a + FGHI(b, c, d) + X[k] + T[i]) <<< s)
*/

static void	ft_update(t_md5_unit *unit)
{
	int		i;
	int		f;

	ft_memcpy(unit->prev_hash, unit->hash, 16);
	i = 0;
	while (i < 63)
	{
		f = g_op[i / 16](unit->hash[1], unit->hash[2], unit->hash[3]);
		unit->hash[0] =
			unit->hash[1] +
			ROTL(unit->hash[0] + f + g_x[i] + g_abssin[i], g_s[i / 16][i % 4]);
		ft_turn_words(unit);
		++i;
	}
	unit->hash[0] += unit->prev_hash[0];
	unit->hash[1] += unit->prev_hash[1];
	unit->hash[2] += unit->prev_hash[2];
	unit->hash[3] += unit->prev_hash[3];
}

BYTE		*ft_md5(const BYTE *m, size_t len)
{
	int			i;
	size_t		left_len;
	size_t		blen;
	t_md5_unit	unit;
	BYTE		*res;

	if (!len)
		len = ft_strlen((char *)m);
	ft_init_unit(&unit);
	i = 0;
	left_len = len;
	blen = len * 8;
	while (1)
	{
		ft_bzero(unit.block.byte, 64);
		if (left_len < 56)
		{
			ft_memcpy(unit.block.byte, &(m[i * 64]), left_len);
			ft_memcpy(&(unit.block.byte[left_len]), g_pad, 56 - left_len);
			ft_memcpy(&(unit.block.byte[55]), &blen, 8);
			left_len = 64;
		}
		else if (left_len < 64)
		{
			ft_memcpy(unit.block.byte, &(m[i * 64]), left_len);
			ft_memcpy(&(unit.block.byte[left_len]), g_pad, 64 - left_len);
			ft_update(&unit);
			ft_bzero(unit.block.byte, 64);
			ft_memcpy(&(unit.block.byte[55]), &blen, 8);
			left_len = 64;
		}
		else
			ft_memcpy(unit.block.byte, &(m[i * 64]), 64);
		ft_update(&unit);
		++i;
		left_len -= 64;
		if (left_len == 64)
		{
			ft_memcpy(unit.block.byte, g_pad, 64);
			ft_memcpy(&(unit.block.byte[55]), &blen, 8);
			ft_update(&unit);
			break ;
		}
		if (!left_len)
			break ;
	}
	res = (BYTE *)ft_smemalloc(16, "ft_md5");
	ft_memcpy(res, unit.hash, 16);
	return (res);
}