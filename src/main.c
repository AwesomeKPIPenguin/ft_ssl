
#include "ssl.h"
#include <stdio.h>

void	ft_usage()
{
	char	*msg;

	msg = "usage: ft_ssl command [command opts] [command args]\n";
	write(1, msg, ft_strlen(msg));
	exit(1);
}

int		main(int ac, char **av)
{
	BYTE	*hash;

	if (ac == 1)
	{
		ft_usage(); // till better times
	}
	else
	{
		hash = ft_md5((BYTE *)(av[1]), ft_strlen(av[1]));
		printf("%x%x%x%x",
			((WORD *)hash)[0], ((WORD *)hash)[1],
			((WORD *)hash)[2], ((WORD *)hash)[3]);
	}
}
