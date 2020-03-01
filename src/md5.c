
#include "md5.h"

static int	*ft_init_array(int op_no, int k, int s, int i)
{
	int		arr[4];

	arr[0] = op_no;
	arr[1] = k;
	arr[2] = s;
	arr[3] = i;
	return (arr);
}

void	ft_init_unit(t_md5_unit *unit)
{
	unit->hash[0] = A;
	unit->hash[1] = B;
	unit->hash[2] = C;
	unit->hash[3] = D;
	unit->op[0] = ft_f;
	unit->op[1] = ft_g;
	unit->op[2] = ft_h;
	unit->op[3] = ft_i;
}

static void	ft_update(t_md5_unit *unit, const int k[4])
{
	unit->oblock[0] =
		unit->oblock[1] + ((
			unit->oblock[0] +
			unit->op[k[0]](unit->oblock[1], unit->oblock[2], unit->oblock[3]) +
			unit->oblock[k[1]] +
			unit->constants[k[3]]
		) << k[2]);
}

void		ft_round_1(t_md5_unit *unit)
{
	ft_process_round_1(unit,  0,  7,  1);
	ft_process_round_1(unit,  1, 12,  2);
	ft_process_round_1(unit,  2, 17,  3);
	ft_process_round_1(unit,  3, 22,  4);
	ft_process_round_1(unit,  4,  7,  5);
	ft_process_round_1(unit,  5, 12,  6);
	ft_process_round_1(unit,  6, 17,  7);
	ft_process_round_1(unit,  7, 22,  8);
	ft_process_round_1(unit,  8,  7,  9);
	ft_process_round_1(unit,  9, 12, 10);
	ft_process_round_1(unit, 10, 17, 11);
	ft_process_round_1(unit, 11, 22, 12);
	ft_process_round_1(unit, 12,  7, 13);
	ft_process_round_1(unit, 13, 12, 14);
	ft_process_round_1(unit, 14, 17, 15);
	ft_process_round_1(unit, 15, 22, 16);
}

static void	ft_process_round_2(t_md5_unit *unit, int k, int s, int i)
{
	unit->oblock[0] =
		unit->oblock[1] + ((
			unit->oblock[0] +
			G(unit->oblock[1], unit->oblock[2], unit->oblock[3]) +
			unit->oblock[k] +
			unit->constants[i]
		) << s);
}

[ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20]
[ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24]
[ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28]
[ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32]

void		ft_round_2(t_md5_unit *unit)
{
	ft_process_round_2(unit,  0,  7,  1);
	ft_process_round_2(unit,  1, 12,  2);
	ft_process_round_2(unit,  2, 17,  3);
	ft_process_round_2(unit,  3, 22,  4);
	ft_process_round_2(unit,  4,  7,  5);
	ft_process_round_2(unit,  5, 12,  6);
	ft_process_round_2(unit,  6, 17,  7);
	ft_process_round_2(unit,  7, 22,  8);
	ft_process_round_2(unit,  8,  7,  9);
	ft_process_round_2(unit,  9, 12, 10);
	ft_process_round_2(unit, 10, 17, 11);
	ft_process_round_2(unit, 11, 22, 12);
	ft_process_round_2(unit, 12,  7, 13);
	ft_process_round_2(unit, 13, 12, 14);
	ft_process_round_2(unit, 14, 17, 15);
	ft_process_round_2(unit, 15, 22, 16);
}

static void	ft_process_round_3(t_md5_unit *unit, int k, int s, int i)
{
	unit->oblock[0] =
		unit->oblock[1] + ((
			unit->oblock[0] +
			H(unit->oblock[1], unit->oblock[2], unit->oblock[3]) +
			unit->oblock[k] +
			unit->constants[i]
		) << s);
}

void		ft_round_3(t_md5_unit *unit)
{
	ft_process_round_1(unit,  0,  7,  1);
	ft_process_round_1(unit,  1, 12,  2);
	ft_process_round_1(unit,  2, 17,  3);
	ft_process_round_1(unit,  3, 22,  4);
	ft_process_round_1(unit,  4,  7,  5);
	ft_process_round_1(unit,  5, 12,  6);
	ft_process_round_1(unit,  6, 17,  7);
	ft_process_round_1(unit,  7, 22,  8);
	ft_process_round_1(unit,  8,  7,  9);
	ft_process_round_1(unit,  9, 12, 10);
	ft_process_round_1(unit, 10, 17, 11);
	ft_process_round_1(unit, 11, 22, 12);
	ft_process_round_1(unit, 12,  7, 13);
	ft_process_round_1(unit, 13, 12, 14);
	ft_process_round_1(unit, 14, 17, 15);
	ft_process_round_1(unit, 15, 22, 16);
}

static void	ft_process_round_4(t_md5_unit *unit, int k, int s, int i)
{
	unit->oblock[0] =
		unit->oblock[1] + ((
			unit->oblock[0] +
			I(unit->oblock[1], unit->oblock[2], unit->oblock[3]) +
			unit->oblock[k] +
			unit->constants[i]
		) << s);
}

void		ft_round_4(t_md5_unit *unit)
{
	ft_process_round_1(unit,  0,  7,  1);
	ft_process_round_1(unit,  1, 12,  2);
	ft_process_round_1(unit,  2, 17,  3);
	ft_process_round_1(unit,  3, 22,  4);
	ft_process_round_1(unit,  4,  7,  5);
	ft_process_round_1(unit,  5, 12,  6);
	ft_process_round_1(unit,  6, 17,  7);
	ft_process_round_1(unit,  7, 22,  8);
	ft_process_round_1(unit,  8,  7,  9);
	ft_process_round_1(unit,  9, 12, 10);
	ft_process_round_1(unit, 10, 17, 11);
	ft_process_round_1(unit, 11, 22, 12);
	ft_process_round_1(unit, 12,  7, 13);
	ft_process_round_1(unit, 13, 12, 14);
	ft_process_round_1(unit, 14, 17, 15);
	ft_process_round_1(unit, 15, 22, 16);
}

char    	*ft_md5(const char *m)
{
	t_md5_unit	unit;
	WORD    	*pm;
	size_t  	m_len;
	int			i;

	/* padding, m_len */

	ft_init_unit(&unit);
	ft_init_constants(unit.constants);
	pm = (WORD *)m;
	i = 0;
	while (i < m_len / 16 - 1)
	{
		ft_memcpy(unit.oblock, &(pm[16 * i]), 16);
		ft_memcpy(unit.prev_hash, unit.hash, 16);

		++i;
	}

}