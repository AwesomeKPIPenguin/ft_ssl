
#include "ssl.h"

void	ft_error_nosuchcommand(t_e *e, int i)
{
	ft_printf(g_err_tmpl_short, e->command_name, "No such command\n");
}

void	ft_error_nosuchflag(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long, e->command_name, e->av[i], "No such flag\n");
}

void	ft_error_noarg(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long,
		e->command_name, e->av[i], "No argument was given\n");
}
