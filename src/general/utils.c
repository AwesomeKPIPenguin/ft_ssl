
#include "ssl.h"

void	ft_init_e(t_e *e, char **av)
{
	ft_bzero(e, sizeof(t_e));
	e->av = av;
	e->fhandlers['p'] = ft_fp;
	e->fhandlers['q'] = ft_fq;
	e->fhandlers['r'] = ft_fr;
}

int		ft_open_file(t_e *e, int i)
{
	int	fd;

	e->file_name = e->av[i];
	if ((fd = open(e->file_name, O_RDONLY)) < 0)
	{
		ft_error_nosuchfile(e, i);
		return (-1);
	}
	if (!(read(fd, NULL, 0)))
	{
		ft_error_badfile(e, i);
		return (-1);
	}
	return (fd);
}

void	ft_hash_process_fd(t_e *e, int fd)
{
	char	buffer[SSL_BSIZE];
	ssize_t	len;
	size_t	total_len;

	if (fd < 0)
		return ;
	total_len = 0;
	while ((len = read(fd, buffer, SSL_BSIZE)) == SSL_BSIZE)
	{
		e->update_hash((BYTE *)buffer, SSL_BSIZE, 0);
		total_len += SSL_BSIZE;
	}
	e->update_hash((BYTE *)buffer, total_len + len, 1);
}
