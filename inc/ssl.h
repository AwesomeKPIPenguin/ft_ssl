
#ifndef SSL_H

# define SSL_H

# include "libftprintf.h"

# include <stdio.h>

# define F_P		0x01
# define F_Q		0x02
# define F_R		0x04
# define F_S		0x08

typedef uint8_t		BYTE;
typedef uint32_t	WORD;

typedef struct		s_e
{
	char			**av;
	char			*command_name;
	BYTE			*(*command)(const BYTE *, size_t);
	void			(*output)(struct s_e *e);
	uint16_t		flags;
	int				(*fhandlers[256])(struct s_e *, int);
	char			*file_name;
	int				is_stdin;
	BYTE			*msg;
	BYTE			*hash;
}					t_e;

int					ft_fp(t_e *e, int i);
int					ft_fq(t_e *e, int i);
int					ft_fr(t_e *e, int i);
int					ft_fs(t_e *e, int i);
void				ft_init_e(t_e *e, char **av);
void				ft_process_msg(t_e *e);
void				ft_process_stdin(t_e *e);

BYTE				*ft_md5(const BYTE *msg, size_t len);
void				ft_md5_init_e(t_e *e);
void				ft_md5_output(t_e *e);

void				ft_error_nosuchcommand(t_e *e, int i);
void				ft_error_nosuchflag(t_e *e, int i);
void				ft_error_noarg(t_e *e, int i);

#endif

