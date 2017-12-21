#include "hmini.h"

int					detect_delimiters(char *inp)
{
	int				i;

	i = -1;
	while (inp[++i] != 0)
	{
		if (inp[i] == '\\')
		{
			if (inp[i + 1] == '&' && inp[i + 2] != '&')
				i += 2;
			else if (inp[i + 1] == '&' && inp[i + 2] == '&')
				i += 3;
			else if (inp[i + 1] == ';')
				i += 2;
			else if (inp[i + 1] == '|')
				i += 2;
			else if (inp[i + 1] == '|' || inp[i + 2] == '|')
				i += 3;
		}
		if (inp[i] == '&')
			return (1);
		else if (inp[i] == '|')
			return (1);
		else if (inp[i] == ';')
			return (1);
	}
	return (0);
}

void				exec_cli_lst(char *inp, t_env *env)
{
	t_listc			*tmp;

//	printf("fe\n");
	if (!detect_delimiters(inp))
	{
//	printf("fa\n");
		exec_cli(inp, env);
	}
	else
	{
		tmp = cut_string_delimiters(inp);
		exec_lst(tmp, env);
	}
}
