
#include "sha256.h"

/*
**	constants
*/

static const WORD	g_k[64] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
   0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
   0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
   0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
   0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
   0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
   0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
   0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
   0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static WORD			g_hash[8] = {
	A, B, C, D, E, F, G, H
};

/*
**	functions
*/

void				ft_sha256_init_e(t_e *e)
{
	e->command_name = ft_strdup("SHA256");
	e->update_hash = ft_sha256_update;
	e->output_hash = ft_sha256_output_hash;
}

void				ft_sha256_output_hash(int isendl)
{
	ft_printf(
		"%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x%s",
		g_hash[0],
		g_hash[1],
		g_hash[2],
		g_hash[3],
		g_hash[4],
		g_hash[5],
		g_hash[6],
		g_hash[7],
		isendl ? "\n" : ""
	);
}

void				ft_sha256_block_update(WORD *b)
{
	WORD	oblock[64];
	WORD	tmp1;
	WORD	tmp2;
	int		i;

	ft_memcpy(oblock, b, 16);
	i = 16;
	while (i < 64)
	{
        oblock[i] = b[i - 7] + b[i - 16]
        	+ ROTR(b[i - 15], 7) ^ ROTR(b[i - 15], 18) ^ (b[i - 15] >> 3)
        	+ ROTR(b[i - 2], 17) ^ ROTR(b[i - 2], 19) ^ (b[i - 2] >> 10);
		++i;
	}
	i = 0;
	while (i < 64)
	{
		tmp1 = g_hash[7]
			+ S(ROTR(g_hash[4], 6), ROTR(g_hash[4], 11), ROTR(g_hash[4], 25))
			+ CH(g_hash[4], g_hash[5], g_hash[6])
			+ g_k[i] + oblock[i];
		tmp2 = S(ROTR(g_hash[0], 2), ROTR(g_hash[0], 13), ROTR(g_hash[0], 22))
			+ MAJ(g_hash[0], g_hash[1], g_hash[2]);
		g_hash[7] += g_hash[6];
		g_hash[6] += g_hash[5];
		g_hash[5] += g_hash[4];
		g_hash[4] += g_hash[3] + tmp1;
		g_hash[3] += g_hash[2];
		g_hash[2] += g_hash[1];
		g_hash[1] += g_hash[0];
		g_hash[0] += tmp1 + tmp2;
		++i;
	}
}

void				ft_sha256_update(const BYTE *msg, size_t len, int is_end)
{
	int			i;
	t_oblock	ob;

	i = 0;
	ob.msg = msg;
	if (is_end)
		ob.blen = len * 8;
	ob.left_len = len % SSL_BSIZE;
	while (1)
		if (!ft_process_hash_block(&ob, ft_sha256_block_update, i++, is_end))
			break ;
}
