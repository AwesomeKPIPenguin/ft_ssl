
#include "ssl.h"

static const BYTE	g_pad[64] = {
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

static void	ft_append_len(BYTE *block, size_t len)
{
	WORD	*wlen;

	wlen = (WORD *)&len;
	if (!wlen[1])
		*((WORD *)(&(block[56]))) = wlen[0];
	else
		*((size_t *)(&(block[56]))) = len;
}

static void	ft_pad_block(
	t_oblock *ob, void (*ft_hash_block_update)(WORD *), const BYTE *msg)
{
	if (ob->left_len < 56)
	{
		ft_memcpy(ob->block.byte, msg, ob->left_len);
		ft_memcpy(
			&(ob->block.byte[ob->left_len]), g_pad, 56 - ob->left_len);
		ft_append_len(ob->block.byte, ob->blen);
		ob->left_len = 64;
	}
	else if (ob->left_len <= 64)
	{
		ft_memcpy(ob->block.byte, msg, ob->left_len);
		ft_memcpy(
			&(ob->block.byte[ob->left_len]), g_pad, 64 - ob->left_len);
		ft_hash_block_update(ob->block.word);
		(ob->left_len == 64)
			? ft_memcpy(ob->block.byte, g_pad, 64)
			: ft_bzero(ob->block.byte, 64);
		ft_append_len(ob->block.byte, ob->blen);
		ob->left_len = 64;
	}
	else
		ft_memcpy(ob->block.byte, ob->msg, 64);
}

int			ft_process_hash_block(
	t_oblock *ob, void (*ft_hash_block_update)(WORD *), int i, int is_end)
{
	ft_bzero(ob->block.byte, 64);
	if (is_end)
		ft_pad_block(ob, ft_hash_block_update, &(ob->msg[i * 64]));
	ft_hash_block_update(ob->block.word);
	ob->left_len -= 64;
	if (is_end && ob->left_len == 64)
	{
		ft_memcpy(ob->block.byte, g_pad, 64);
		ft_append_len(ob->block.byte, ob->blen);
		ft_hash_block_update(ob->block.word);
		return (0);
	}
	if (!ob->left_len)
		return (0);
	return (1);
}
