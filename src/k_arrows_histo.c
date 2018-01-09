#include "hmini.h"

t_histo				*histo_init(void)
{
	t_histo			*outp;

	if (!(outp = malloc(sizeof(t_histo))))
		ft_error(MAF, -1);
	outp->cont = NULL;
	outp->prev = NULL;
	outp->next = NULL;
	return (outp);
}

t_histo				*new_cmd_histo(int read_mode, t_histo **history)
{
	t_histo			*new_cmd;
	t_histo			*cursor;

	if (!read_mode)
		return (NULL);
	if (!(new_cmd = histo_init()))
		ft_error(MAF, -1);
	cursor = *history;
	if (!(*history))
		return (new_cmd);
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = new_cmd;
	new_cmd->prev = cursor;
	return (new_cmd);

}

void				del_old(t_histo **history)
{
	int				i;
	t_histo			*cursor;

	i = 0;
	cursor = *history;
	while (cursor->next != NULL)
		cursor = cursor->next;
	*history = cursor;
	while (cursor->prev != NULL)
	{
		cursor = cursor->prev;
		i++;
	}
	if (i > MAX_HISTO)
		while (i-- > MAX_HISTO && cursor->next)
		{
			cursor->cont ? free(cursor->cont) : 0;
			cursor = cursor->next;
			cursor->prev ? free(cursor->prev) : 0;
			cursor->prev = NULL;
		}
}

void				register_history(char **to_fill, t_histo **history,
						char *scribe)
{
	t_histo			*cursor;
	int				i[2];

	cursor = *history;
	i[0] = -1;
	i[1] = 0;
	while (scribe[++i[0]])
		if (scribe[i[0]] > 32)
			i[1]++;
	while (cursor->next != NULL)
		cursor = cursor->next;
	if (!i[1] && cursor->prev)
	{
		cursor->cont ? free(cursor->cont) : 0;
		cursor = cursor->prev;
		free(cursor->next);
		cursor->next = NULL;
		*history = cursor;
		*to_fill = scribe;
		return ;
	}
	cursor->cont ? free(cursor->cont) : 0;
	cursor->cont = ft_strdup(scribe);
	del_old(history);
	*to_fill = scribe;
}

unsigned int		k_arrows_histo(int down, unsigned int cursor,
						t_histo **history, char **scribe)
{
	size_t			i[2];

	i[0] = 0;
	if ((down && !(*history)->next) || (!down && !(*history)->prev))
		return (cursor);
	(*history)->cont ? free((*history)->cont) : 0;
	(*history)->cont = *scribe;
	if (down)
		*history = (*history)->next;
	else
		*history = (*history)->prev;
	i[1] = ft_strlen(*scribe);
	if (cursor >= 1)
		move_back(cursor);
	while (i[0]++ <= i[1])
		write(1, " ", 1);
	move_back(i[1] + 1);
	ft_putstr((*history)->cont);
	*scribe = ft_strdup((*history)->cont);
	return ((unsigned int)ft_strlen(*scribe));
}
