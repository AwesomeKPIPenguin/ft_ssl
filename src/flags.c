
#include "ssl.h"

int		ft_fp(t_e *e, int i)
{
	if (!(e->flags & F_P)
		&& (!ft_strcmp(e->command_name, "MD5")
			|| !ft_strcmp(e->command_name, "SHA256")))
	{
		e->flags |= F_P;
	}
	return (i);
}

int		ft_fq(t_e *e, int i)
{
	if (!(e->flags & F_Q)
		&& (!ft_strcmp(e->command_name, "MD5")
			|| !ft_strcmp(e->command_name, "SHA256")))
	{
		e->flags |= F_Q;
	}
	return (i);
}

int		ft_fr(t_e *e, int i)
{
	if (!(e->flags & F_R)
		&& (!ft_strcmp(e->command_name, "MD5")
			|| !ft_strcmp(e->command_name, "SHA256")))
	{
		e->flags |= F_R;
	}
	return (i);
}

int		ft_fs(t_e *e, int i)
{
	if (!(e->flags & F_S)
		&& (!ft_strcmp(e->command_name, "MD5")
			|| !ft_strcmp(e->command_name, "SHA256")))
	{
		if (!(e->av[i + 1]))
		{
			ft_error_noarg(e, i);
			return (i);
		}
		e->msg = (BYTE *)e->av[i + 1];
		e->flags |= F_S;
		return (i + 1);
	}
}
