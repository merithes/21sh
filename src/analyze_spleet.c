#include "hmini.h"

int			isnum(char *inp)
{
	int		i;

	i = 0;
	while (inp && inp[i])
	{
		if (inp[i] <= '0' || inp[i] >= '9')
			return (0);
		i++;
	}
	return (1);
}

int			isredir(char *inp)
{
	if (!inp || (!ft_strcmp(inp, "<<") && !ft_strcmp(inp, "<") &&
		!ft_strcmp(inp, ">>") && !ft_strcmp(inp, ">")))
		return (0);
	return (1);
}

void		recat_stuff(char **a)
{
	int		len;
	char	*tmp;

	len = ft_strlen(a[1]) + ft_strlen(a[2]);
	tmp = ft_strnew(len + 1);
	ft_strcat(tmp, a[1]);
	ft_strcat(tmp, a[2]);
	free(a[1]);
	a[1] = tmp;
	free(a[2]);
	a[2] = NULL;
}

int			analyze_spleet(char *a[4], t_list **tmp_a, t_list **tmp_b)
{
	int		i;

	if (!a[1])
		return (0);
	if (!isredir(a[0]) && !isredir(a[1]))
		return (0);
	if (isnum(a[0]) && isnum(a[2] + 1) && a[2][0] == '&'
		&& (!ft_strcmp(a[1], "<") || !ft_strcmp(a[1], ">")))
		return (0);
	else if (!isnum(a[0]) && isnum(a[2] + 1) && a[2][0] == '&' &&
	 	!ft_strcmp(a[1], ">"))
		recat_stuff(a);
	i = 0;
	*tmp_a = ft_lstnew(NULL, 0);
	if (!a[0] || !a[0][0])
	{
		if (a[0] != NULL && !a[0][0])
			free(a[0]);
		i++;
	}
	(*tmp_a)->content = a[i++];
	*tmp_b = *tmp_a;
	(*tmp_b)->next = ft_lstnew(NULL, 0);
	(*tmp_b)->next->content = a[i++];
	*tmp_b = (*tmp_b)->next;
	if (a[i] && a[i][0])
	{
		(*tmp_b)->next = ft_lstnew(NULL, 0);
		(*tmp_b)->next->content = a[i];
		*tmp_b = (*tmp_b)->next;
	}
	return (1);
}
