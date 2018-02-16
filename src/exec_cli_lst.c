#include "hmini.h"

int ghgh = 0;

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	int				err;
	char			**split_alt;
	int				i;

	tmp = NULL;
	split_alt = splitter_alt(inp);
	split_alt = detect_bad_delimiters(split_alt);
//	if (++ghgh == 2){printf("hoh\t%p\n", split_alt[0]);free(split_alt[0]);printf("huh\n");}
	if ((err = lex_splitted(split_alt)) != 0)
	{
		i = -1;
		while (split_alt[++i])
		{
//			printf("freeing %p\t%s\n", split_alt[i], split_alt[i]);
			free(split_alt[i]);
		}
		free(split_alt);
		split_alt = NULL;
	}
	if (split_alt != NULL)
	{
		if ((tmp = cut_string_delimiters(split_alt)) != NULL)
/*			if (!parse_errors_lst(tmp) && !expand_set_redirs(tmp))*/
				exec_lst(tmp, env);
	}
	split_alt ? free(split_alt) : 0;
}
