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
/*	printf("%p\n", split_alt);
	printf("%p:%s\n", split_alt[0], split_alt[0]);
	if(split_alt[1])
	printf("%p:%s\n", split_alt[1], split_alt[1]);
	if(split_alt[2])
	printf("%p:%s\n", split_alt[2], split_alt[2]);
	printf("%p\n", split_alt[3]);
	int i ;
	i = -1 ;
	while (split_alt[++i]) printf("|%s|\n", split_alt[i]);
	printf("WOOT\n");*/
	char **split_alt_2=split_alt;
	int i=-1;while(split_alt_2[++i])printf("%s\n", split_alt_2[i]);
	detect_bad_delimiters(&split_alt);
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
