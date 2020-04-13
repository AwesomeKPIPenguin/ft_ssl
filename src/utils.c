
#include "ssl.h"

void	ft_init_e(t_e *e)
{
	ft_bzero(e, sizeof(t_e));
	e->fhandlers['p'] = ft_fp;
	e->fhandlers['q'] = ft_fq;
	e->fhandlers['r'] = ft_fr;
}
