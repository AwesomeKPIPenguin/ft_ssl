
#include "ssl.h"

static const char	*g_err_tmpl_short = "ft_ssl: %s: %s";
static const char	*g_err_tmpl_long = "ft_ssl: %s: %s: %s";

void				ft_error_nosuchcommand(t_e *e, int i)
{
	i = i;
	ft_printf(g_err_tmpl_short, e->command_name, "No such command\n");
}

void				ft_error_nosuchflag(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long, e->command_name, e->av[i], "No such flag\n");
}

void				ft_error_noarg(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long,
		e->command_name, e->av[i], "No argument was given\n");
}

void				ft_error_nosuchfile(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long,
		e->command_name, e->av[i], "File not found\n");
}

void				ft_error_badfile(t_e *e, int i)
{
	ft_printf(g_err_tmpl_long,
		e->command_name, e->av[i], "Not a file or unable to read\n");
}
