#include "hmini.h"

int					cnt_splitters(char *inp)
{
	int				i;
	int				count;

	count = 0;
	i = -1;
	if (inp[0] == '\'' || inp[0] == '\"' || !ft_strcmp(inp, ";") ||
		!ft_strcmp(inp, "|") || !ft_strcmp(inp, "&") || !ft_strcmp(inp, "||") ||
			!ft_strcmp(inp, "&&"))
		return (0);
	while (inp[++i])
	{
	printf("a\n");
		if (inp[i] == ';')
			count++;
		else if (inp[i] == '|' || inp[i] == '&')
		{
			if ((inp[i + 1] == '|' && inp[i] == '|')
				|| (inp[i + 1] == '|' && inp[i] == '&'))
				i++;
			count++;
		}
	printf("b\n");
	}
	printf("c\n");
	return (count);
}

int					detect_bad_delimiters(char ***inp)
{
	int				i;
	int				count;
	char			**re_splitted;

	i = -1;
	count = 0;
//	printf("truc\n");
	if (!*inp)
		return (-1);
	while (*inp[++i])
	{
//		printf("1a\n");
		count += cnt_splitters(*inp[i]);
//		printf("1b:%d\n%p:%s\n", i, *inp[i], *inp[i]);
	}
	printf("truc\n");
	if (!count)
		return (0);
	if (!(re_splitted = malloc(sizeof(char *) *
		(ft_pointertablen(*inp) + count * 2))))
		ft_error("FailedMemory Allocation.\n", -1);
	printf("truc\n");
	return(1);
}

int					detect_delimiters(char **inp)
{
	int				i;

	i = -1;
	while (inp[++i] != NULL)
	{
		if (!ft_strcmp("|", inp[i]))
			return (1);
		else if (!ft_strcmp(";", inp[i]))
			return (1);
		else if (!ft_strcmp("||", inp[i]))
			return (1);
		else if (!ft_strcmp("&&", inp[i]))
			return (1);
	}
	return (0);
}
