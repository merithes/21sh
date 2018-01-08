#include "hmini.h"

void				interp_cont_exec(char **cont, t_env *env)
{
	int				i;
	char			*tmp;

	i = -1;
	while (cont != NULL && cont[++i] != NULL)
	{
		if ((tmp = line_env_interpret(cont[i], env)) != NULL)
		{
			free(cont[i]);
			cont[i] = tmp;
		}
	}
}

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	char			**split_alt;

	tmp = NULL;
	split_alt = splitter_alt(inp);
	detect_bad_delimiters(split_alt);
	if (split_alt != NULL && !detect_delimiters(split_alt))
	{
//		printf("a\n");
		tmp = create_chain_link(NULL);
		tmp->cont = split_alt;
		interp_cont_exec(tmp->cont, env);
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
