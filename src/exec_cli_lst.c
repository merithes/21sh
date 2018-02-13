#include "hmini.h"

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	int				err;
	char			**split_alt;

	tmp = NULL;
	split_alt = splitter_alt(inp);
//	if (detect_wrong_redirs(split_alt))
//		return ;
	split_alt = detect_bad_delimiters(split_alt);
	if ((err = lex_splitted(split_alt)) != 0)
	{
		printf("%d\n", err);
		free_rec_char(split_alt);
		split_alt = NULL;
	}
//	split_alt = resplit_bad_redirs(split_alt);
	//int i = -1;while (split_alt && split_alt[++i]) printf("%d:\t%s\n", i, split_alt[i]);
	if (split_alt != NULL)
	{
		if ((tmp = cut_string_delimiters(split_alt)) != NULL)
/*			if (!parse_errors_lst(tmp) && !expand_set_redirs(tmp))*/
				exec_lst(tmp, env);
	}
	split_alt ? free(split_alt) : 0;
}
