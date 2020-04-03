
#include "ssl.h"
#include <stdio.h>

void	ft_usage()
{
	char	*msg;

	msg = "usage: ft_ssl command [command opts] [command args]\n";
	write(1, msg, ft_strlen(msg));
	exit(1);
}

void	ft_process_command(t_e *e, char **av)
{
	e->command_name = av[1];
	if (!ft_strcmp(av[1], "md5"))
		e->command = ft_md5;
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
			if (g_fhandlers[av[i][1]])
				i = g_fhandlers[av[i][1]](e, i);
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
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-s"))
			i = ft_fs(e, i);
		else
			/* ft_handle_file() */ ;
		e->hash = e->command(e->msg, ft_strlen((char *)e->msg));
		/* e->command_output(e); */
		++i;
	}
}

int		main(int ac, char **av)
{
	BYTE	*hash;
	t_e		e;

	e.av = av;
	e.file_name = 0;
	if (ac == 1)
		ft_usage();
	else
		ft_process_args(&e, ac, av);
}
