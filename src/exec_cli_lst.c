#include "hmini.h"

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

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	char			**split_alt;

	tmp = NULL;
	split_alt = splitter_alt(inp);
	if (split_alt != NULL && !detect_delimiters(split_alt))
	{
//		printf("a\n");
		tmp = create_chain_link(NULL);
		tmp->cont = split_alt;
		exec_cli(inp, tmp, env);
		free_rec_char(split_alt);
		split_alt = 0;
		free(tmp);
	}
	else if (split_alt != NULL)
	{
		if ((tmp = cut_string_delimiters(split_alt)) != NULL)
			exec_lst(tmp, env);
		else
			return ;
	}
	split_alt ? free(split_alt) : 0;
}
