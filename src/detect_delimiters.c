#include "hmini.h"

static int			detect_grouped_delim(char *inp)
{
}

int					cnt_splitters(char *inp)
{
	int				i;
	int				count;

	i = -1;
	if (inp[0] == '\'' || inp[0] == '\"' || !ft_strcmp(inp, ";") ||
		!ft_strcmp(inp, "|") || !ft_strcmp(inp, "&") || !ft_strcmp(inp, "||") ||
			!ft_strcmp(inp, "&&"))
		return (0);
	while (inp[++i])
	{
		if (inp[i] == ';')
			count++;
		else if (inp[i] == '|' || inp[i] == '&')
			if; 
	}
}

int					detect_bad_delimiters(char ***inp)
{
	int				i;
	int				count;
	char			**re_splitted;

	i = -1;
	count = 0;
	while (*inp[++i])
		count += cnt_splitters(*inp[i]);
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
