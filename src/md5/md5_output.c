
#include "md5.h"

static void	ft_md5_output_hash(const BYTE *hash, int isendl)
{
	ft_printf(
		"%.8x%.8x%.8x%.8x%s",
		*(WORD *)(&(hash[0])),
		*(WORD *)(&(hash[4])),
		*(WORD *)(&(hash[8])),
		*(WORD *)(&(hash[12])),
		isendl ? "\n" : ""
	);
}

static void	ft_md5_output_name(t_e *e, int isendl)
{
	if (e->file_name)
		ft_printf("%s%s", e->file_name, isendl ? "\n" : "");
	else
		ft_printf("\"%s\"%s", e->msg, isendl ? "\n" : "");
}

static void	ft_md5_output_stdin(t_e *e)
{
	if (e->flags & F_P)
		ft_printf("%s\n", e->msg);
	ft_md5_output_hash(e->hash, 1);
}

static void	ft_md5_output_arg(t_e *e)
{
	if (e->flags & F_Q)
		ft_md5_output_hash(e->hash, 1);
	else
	{
		if (e->flags & F_R)
		{
			ft_md5_output_hash(e->hash, 0);
			ft_printf(" ");
			ft_md5_output_name(e, 1);
		}
		else
		{
			ft_printf("%s (", e->command_name);
			ft_md5_output_name(e, 0);
			ft_printf(") = ");
			ft_md5_output_hash(e->hash, 1);
		}
	}
}

void		ft_md5_output(t_e *e)
{
	if (e->msg)
	{
		if (e->is_stdin)
			ft_md5_output_stdin(e);
		else
			ft_md5_output_arg(e);
	}
	e->is_stdin = 0;
}
