
#include "ssl.h"

void	ft_usage()
{
	char	*msg;

	msg = "usage: ft_ssl command [command opts] [command args]\n";
	write(1, msg, ft_strlen(msg));
	exit(1);
}

int		main(int ac, char **av)
{
	if (ac == 1)
	{
		ft_usage(); // till better times
	}
	else
	{
		
	}
}
