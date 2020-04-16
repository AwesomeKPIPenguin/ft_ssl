
#include "ssl.h"

void	ft_init_e(t_e *e, char **av)
{
	ft_bzero(e, sizeof(t_e));
	e->av = av;
	e->fhandlers['p'] = ft_fp;
	e->fhandlers['q'] = ft_fq;
	e->fhandlers['r'] = ft_fr;
}

void	ft_process_stdin(t_e *e)
{
	char	*buffer;
	char	*tmp;
	ssize_t	len;

	e->msg = (BYTE *)ft_strnew(1, 0);
	buffer = ft_strnew(BUFF_SIZE, 0);
	while ((len = read(0, buffer, BUFF_SIZE)))
	{
		buffer[len - 1] = 0;
		tmp = ft_strjoin((char *)e->msg, buffer);
		free(e->msg);
		ft_bzero(buffer, BUFF_SIZE + 1);
		e->msg = (BYTE *)tmp;
	}
	free(buffer);
	e->is_stdin = 1;
	ft_process_msg(e);
	e->is_stdin = 0;
	free(e->msg);
}
