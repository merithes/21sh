#include "hmini.h"

char			*cpy_first(char *inp, int *stf)
{
	int			i;
	int			len;
	char		*set;

	i = -1;
	len = -1;
	while (inp[++i])
		if (inp[i] == '<' || inp[i] == '>')
			break ;
		else if (inp[i] == '\\')
			i++;
	set = malloc(i + 1);
	bzero(set, i + 1);
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
	set = malloc(i + 1);
	bzero(set, i + 1);
	set[0] = inp[0];
	*stf = i;
	if (i == 2)
		set[1] = inp[1];
	return (set);
}

int				main(int ac, char **av)
{
	int			i;
	int			stf;
	char		*a[4];

	bzero(a, 4 * sizeof(char *));
	a[0] = cpy_first(av[1], &stf);
	av[1] += stf;
	a[1] = cpy_token(av[1], &stf);
	av[1] += stf;
	if (stf)
		a[2] = strdup(av[1]);

	printf("%p\t%p\t%p\n", a[0], a[1], a[2]);
	printf("|%s|\t|%s|\t|%s|\n", a[0], a[1], a[2]);
}
