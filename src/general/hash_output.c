
#include "ssl.h"

static void	ft_hash_output_name(t_e *e, int isendl)
{
	if (e->file_name)
		ft_printf("%s%s", e->file_name, isendl ? "\n" : "");
	else
		ft_printf("\"%s\"%s", e->msg, isendl ? "\n" : "");
}

static void	ft_hash_output_stdin(t_e *e)
{
	if (e->flags & F_P)
		ft_printf("%s\n", e->msg);
	e->output_hash(1);
}

static void	ft_hash_output_arg(t_e *e)
{
	if (e->flags & F_Q)
		e->output_hash(1);
	else
	{
		if (e->flags & F_R)
		{
			e->output_hash(0);
			ft_printf(" ");
			ft_hash_output_name(e, 1);
		}
		else
		{
			ft_printf("%s (", e->command_name);
			ft_hash_output_name(e, 0);
			ft_printf(") = ");
			e->output_hash(1);
		}
	}
}

void		ft_hash_output(t_e *e)
{
	if (e->msg)
	{
		if (e->is_stdin)
			ft_hash_output_stdin(e);
		else
			ft_hash_output_arg(e);
	}
	e->is_stdin = 0;
}
