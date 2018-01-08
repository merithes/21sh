#include "hmini.h"

static int			detect_grouped_delim(char *inp)
{
	int				counter;
	char			*tmp[2];

	counter = 0;
		return (0);
	tmp[0] = (char *)0xffffffffffff;
	while (inp)
	{
		tmp[0] = NULL;
		tmp[1] = (char *)0xffffffffffff;
		if ((tmp[0] = ft_strstr(inp, ";")) != NULL)
			tmp[1] = (tmp[0] < tmp[1]) ? tmp[0] : tmp[1];
		else if ((tmp[0] = ft_strstr(inp, "|")) != NULL)
			tmp[1] = (tmp[0] < tmp[1]) ? tmp[0] : tmp[1];
		else if ((tmp[0] = ft_strstr(inp, "&&")) != NULL)
			tmp[1] = (tmp[0] < tmp[1]) ? tmp[0] : tmp[1];
		else if ((tmp[0] = ft_strstr(inp, "||")) != NULL)
			tmp[1] = (tmp[0] < tmp[1]) ? tmp[0] : tmp[1];
		else if ((tmp[0] = ft_strstr(inp, "&")) != NULL)
			tmp[1] = (tmp[0] < tmp[1]) ? tmp[0] : tmp[1];
		counter = (tmp[0] != NULL) ? 1 : 0;
	}
	return (counter);
}

char				**resplit(char **inp, int add)
{
	int				i;
	char			**outp;

	i = -1;
	if (!(outp = malloc(sizeof(char *) * (ft_pointertablen(inp) + add))))
		ft_error("Memory Allocation Failed.\n", -1);
	while (inp[++i])
	{
		if (inp[i][0] != '\'' && inp[i][0] != '\"' &&
			detect_grouped_delim(inp[i]))
	}
}

int					detect_bad_delimiters(char ***inp)
{
	int				i;
	int				resplit_count;
	char			**re_splitted;

	i = -1;
	resplit_count = 0;
	while (*inp[++i] != NULL)
	{
		if (*inp[i][0] != '\'' && *inp[i][0] != '\"' &&
			ft_strlen(*inp[0]) != 1 && !(ft_strlen(*inp[0]) == 2 &&
				((*inp[0][0] == '&' && *inp[0][1] == '&') || (*inp[0][0] == '|'
					&& *inp[0][1] == '|')))
			detect_grouped_delim(*inp[i]))
			resplit_count++;
	}
	re_splitted = resplit(*inp, resplit_count);
	free(*inp);
	*inp = re_splitted;
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
