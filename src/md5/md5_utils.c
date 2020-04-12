
#include "md5.h"

void	ft_md5_init_e(t_e *e)
{
	e->command_name = ft_strdup("MD5");
	e->command = ft_md5;
	e->output = ft_md5_output;
}
