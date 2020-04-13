
#include "ssl.h"

void	ft_process_command(t_e *e, char **av)
{
	e->command_name = av[1];
	if (!ft_strcmp(av[1], "md5"))
		ft_md5_init_e(e);
	else if (!ft_strcmp(av[1], "sha256"))
		;
//		e->command = ft_sha256;
	else
	{
		ft_error_nosuchcommand(e, 1);
		exit(-1);
	}
}

int		ft_process_flags(t_e *e, int ac, char **av)
{
	int	i;

	i = 2;
	while (i < ac && av[i][0] == '-')
	{
		if (!av[i][2])
		{
			if (av[i][1] == 's')
				return (i);
			if (e->fhandlers[(int)av[i][1]])
				i = e->fhandlers[(int)av[i][1]](e, i);
			else
				ft_error_nosuchflag(e, i);
		}
		else
			ft_error_nosuchflag(e, i);
		++i;
	}
	return (i);
}

void	ft_process_args(t_e *e, int ac, char **av)
{
	int		i;

	ft_process_command(e, av);
	i = ft_process_flags(e, ac, av);
	if (ac == 2 || e->flags & F_P)
		ft_process_stdin(e);
	while (i < ac)
	{
		e->file_name = NULL;
		e->flags &= ~F_S;
		if (!ft_strcmp(av[i], "-s"))
			i = ft_fs(e, i);
		else
		{
			e->file_name = av[i];
			e->msg = (BYTE *)ft_readfile(av[i]);
		}
		ft_process_msg(e);
		++i;
	}
}

int		main(int ac, char **av)
{
	t_e		e;

	ft_init_e(&e);
	if (ac == 1)
	{
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
		return (-1);
	}
	else
	{
		ft_process_args(&e, ac, av);
	}
	return (0);
}
