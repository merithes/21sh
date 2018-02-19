#include "hmini.h"

char			*cpy_first(char *inp, int *stf)
{
	int			i;
	int			len;
	char		*set;

	i = -1;
	len = -1;
	while (inp[++i])
	{
		if (inp[i] == '<' || inp[i] == '>')
			break ;
		else if (inp[i] == '\\')
			i++;
	}
	if (!i)
	{
		*stf = 0;
		return (NULL);
	}
	set = (char *)malloc(i + 2);
	bzero(set, i + 2);
	while (++len < i)
		set[len] = inp[len];
	*stf = len;
	return (set);
}

char			*cpy_token(char *inp, int *stf)
{
	char		*set;
	int			i;

	if (inp[0] == '>' || inp[0] == '<')
	{
		if (inp[1] == inp[0])
			i = 2;
		else
			i = 1;
	}
	else
	{
		*stf = 0;
		return (NULL);
	}
	set = (char *)malloc(i + 5);
	bzero(set, i + 2);
	set[0] = inp[0];
	*stf = i;
	if (i == 2)
		set[1] = inp[1];
	return (set);
}

int				spleet(char *av, char **a, t_list **tmp_a, t_list **tmp_b)
{
	int			stf;

	stf = 0;
	a[0] = cpy_first(av, &stf);
	av += stf;
	a[1] = cpy_token(av, &stf);
	av += stf;
	if (ft_strlen(av) > 0)
		a[2] = (char *)strdup(av);
	else
		a[2] = NULL;
	return (analyze_spleet(a, tmp_a, tmp_b));
}

t_list			*correct_redir(t_list *inp, t_list **cursor)
{
	char		*spleetd[4];
	t_list		*tmp_a;
	t_list		*tmp_b;

	*cursor = NULL;
	ft_bzero(spleetd, sizeof(char *) * 4);
	if (!inp || !inp->content)
	{
		if (cursor && *cursor)
			*cursor = (*cursor)->next;
		return (NULL);
	}
	if (spleet(inp->content, spleetd, &tmp_a, &tmp_b))
	{
//	printf("{\\_|%s|\t|%s|\t|%s|\n", spleetd[0], spleetd[1], spleetd[2]);
		*cursor = tmp_b;
		(inp && inp->content) ? free(inp->content) : 0;
		(inp) ? free(inp) : 0;
		return (tmp_a);
	}
	return (inp);
}

t_list			*check_redirs(t_list *inp)
{
	t_list		*outp;
	t_list		*cursor;
	t_list		*cursor_b;

	outp = correct_redir(inp, &cursor);
	if (!cursor)
		cursor = outp;
	while (cursor && cursor->next)
	{
		cursor_b = NULL;
		cursor->next = correct_redir(cursor->next, &cursor_b);
		if (cursor_b)
			cursor = cursor_b;
		else
			cursor = cursor->next;
		cursor_b = outp;
		while (cursor_b)
		{
			cursor_b = cursor_b->next;
		}
	}
	return(outp);
}	
