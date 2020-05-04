
#ifndef SSL_H

# define SSL_H

# include "libftprintf.h"

# include <stdio.h>

# define SSL_BSIZE	1024

# define F_P		0x01
# define F_Q		0x02
# define F_R		0x04
# define F_S		0x08

# define ROTL(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))
# define ROTR(x, n)	(((x) >> (n)) | ((x) << (32 - (n))))

typedef uint8_t		BYTE;
typedef uint32_t	WORD;

typedef struct		s_e
{
	char			**av;
	char			*command_name;
	void			(*update_hash)(const BYTE *, size_t, int);
	void			(*output_hash)(int);
	uint16_t		flags;
	int				(*fhandlers[256])(struct s_e *, int);
	char			*file_name;
	int				is_stdin;
	BYTE			*msg;
	BYTE			*hash;
}					t_e;

typedef union		u_block
{
	BYTE			byte[64];
	WORD			word[16];
}					t_block;

typedef struct		s_oblock
{
	const BYTE		*msg;
	t_block			block;
	size_t			left_len;
	size_t			blen;
}					t_oblock;

/*
**	general
*/

void				ft_init_e(t_e *e, char **av);
int					ft_open_file(t_e *e, int i);
void				ft_error_nosuchcommand(t_e *e, int i);
void				ft_error_nosuchflag(t_e *e, int i);
void				ft_error_noarg(t_e *e, int i);
void				ft_error_nosuchfile(t_e *e, int i);
void				ft_error_badfile(t_e *e, int i);

/*
**	hash
*/

int					ft_fp(t_e *e, int i);
int					ft_fq(t_e *e, int i);
int					ft_fr(t_e *e, int i);
int					ft_fs(t_e *e, int i);
void				ft_hash_process_fd(t_e *e, int fd);
int					ft_process_hash_block(
						t_oblock *ob,
						void (*ft_hash_block_update)(WORD *),
						int i,
						int is_end
					);
void				ft_hash_output(t_e *e);

/*
**	md5
*/

void				ft_md5_update(const BYTE *msg, size_t len, int is_end);
void				ft_md5_init_e(t_e *e);
void				ft_md5_encode(void);
void				ft_md5_output_hash(int isendl);

/*
**	sha256
*/

void				ft_sha256_update(const BYTE *msg, size_t len, int is_end);
void				ft_sha256_init_e(t_e *e);
void				ft_sha256_output_hash(int isendl);

#endif

