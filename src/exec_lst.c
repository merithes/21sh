#include "hmini.h"

void				exec_lst(t_listc *inp, t_env *env)
{
	char			*temp;

	while (inp)
	{
		if (inp->sep_type == SEPA || inp->sep_type == NONE)
		{
			temp = ft_strdup(inp->cont);
			temp = line_env_interpret(temp, env);
			exec_cli(temp, env);
			free(temp);
		}
		else if (inp->sep_type == PIPE)
			printf("a\n");;
		if (inp->sep_type == NONE)
			break;
		inp = inp->next;
	}
}
