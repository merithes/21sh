#include "hmini.h"

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	char			**split_alt;

	tmp = NULL;
	split_alt = splitter_alt(inp);
	split_alt = detect_bad_delimiters(split_alt);
	if (split_alt != NULL)
	{
		if ((tmp = cut_string_delimiters(split_alt)) != NULL)
			exec_lst(tmp, env);
		else
			return ;
	}
	split_alt ? free(split_alt) : 0;
}
