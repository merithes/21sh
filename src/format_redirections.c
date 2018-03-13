#include "hmini.h"

void				erase_args(char **inp, int index, int type)
{
	free(inp[index]);
	if (type == 2)
		free(inp[index + 1]);
	while (inp[index + type])
	{
		inp[index] = inp[index + type];
		index++;
	}
	inp[index] = NULL;
	inp[index + 1] = NULL;
	if (type == 2)
		inp[index + 2] = NULL;
}

t_redir				*create_redir(int fd, int type, int recep, char *file)
{
	t_redir			*outp;

	if (!(outp = malloc(sizeof(t_redir) + 1)))
		ft_error(MAF, -1);
	ft_bzero(outp, sizeof(t_redir) + 1);
	outp->file = file ? ft_strdup(file) : NULL;
	outp->redir[0] = fd;
	outp->redir[1] = type;
	outp->redir[2] = recep;
	outp->next = NULL;
	return (outp);
}

void				redir_simple_format(char **inp, int i, t_listc *lnk)
{
	int				redir[3];
	t_redir			*tmp;

	redir[0] = 1;
	if (!ft_strcmp(inp[i], "<<"))
		redir[1] = 2;
	else if (!ft_strcmp(inp[i], "<"))
	{
		redir[0] = 0;
		redir[1] = 0;
	}
	else if (!ft_strcmp(inp[i], ">"))
		redir[1] = 1;
	else if (!ft_strcmp(inp[i], ">>"))
		redir[1] = 3;
	else
		redir[1] = -1;
	if (!(lnk->redirs))
	   lnk->redirs = create_redir(redir[0], redir[1], 0, inp[i + 1]);
	else
	{
		tmp = lnk->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_redir(redir[0], redir[1], 0, inp[i + 1]);
	}
}

void				redir_nsimple_format(char **inp, int index, t_listc *lnk)
{
	int				redir[3];
	int				i;
	t_redir			*tmp;

	redir[1] = 1;
	if (inp[index][0] >= '0' && inp[index][0] <= '9')
	{
		redir[0] = ft_atoi(inp[index]);
	}
	else
		redir[0] = 1;
	i = 0;
	while (inp[index][i] >= '0' && inp[index][i] <= '9')
		i++;
	i += 2;
	redir[2] = ft_atoi(inp[index] + i);
//	check_fd(redir[2]);
	if (!(lnk->redirs))
	   lnk->redirs = create_redir(redir[0], redir[1], redir[2], inp[i + 1]);
	else
	{
		tmp = lnk->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_redir(redir[0], redir[1], redir[2], inp[i + 1]);
	}
}
