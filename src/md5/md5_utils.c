
#include "md5.h"

void	ft_md5_init_e(t_e *e)
{
	e->command_name = ft_strdup("MD5");
	e->command = ft_md5;
	e->output = ft_md5_output;
}

void	ft_process_msg(t_e *e)
{
	e->hash = e->command(e->msg, ft_strlen((char *)e->msg));
	e->output(e);
	free(e->hash);
}

void	ft_process_stdin(t_e *e)
{
	char	*tmp;

	tmp = NULL;
	while (get_next_line(0, &tmp))
	{
		e->msg = (BYTE *)ft_strjoin((char *)e->msg, tmp);
		free(tmp);
		tmp = NULL;
	}
	ft_process_msg(e);
}
