#include "hmini.h"

int					contains_bad_redirs(char *inp)
{
	int				i;

	i = -1;
	if (!inp)
		return (0);
	if (!ft_strcmp(inp, ">") || !ft_strcmp(inp, ">>") || !ft_strcmp(inp, "<")
		|| !ft_strcmp(inp, "<<"))
		return (0);
	while (inp[++i])
	{
		if (inp[i] == '<' || inp[i] == '>')
			return (1);
		else if (inp[i] == '\\')
			i++;
	}
	return (0);
}
