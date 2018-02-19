#include "hmini.h"

void				display_lexing_err(int err, char *inp)
{
	if (err == ERR_1)
		ft_putstr_fd(ERRP1, 2);
	if (err == ERR_2)
		ft_putstr_fd(ERRP2, 2);
	if (err == ERR_3)
		ft_putstr_fd(ERRP3, 2);
	if (err == ERR_4)
		ft_putstr_fd(ERRP4, 2);
	err ? ft_putstr_fd(inp, 2) : ft_putstr_fd("newline", 2);
	ft_putstr_fd("' (", 2);
	ft_putnbr_fd(err, 2);
	ft_putstr_fd(").\n", 2);
}

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;
	int				err;
	char			**split_alt;
	int				i;
	char			*err_token;

	tmp = NULL;
	split_alt = splitter_alt(inp);
	split_alt = detect_bad_delimiters(split_alt);
	if ((err = lex_splitted(split_alt, &err_token)) != 0)
	{
		i = -1;
		display_lexing_err(err, err_token);
		err_token = NULL;
		while (split_alt[++i])
			free(split_alt[i]);
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
