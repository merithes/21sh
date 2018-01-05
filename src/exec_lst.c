#include "hmini.h"

void				exec_lst(t_listc *inp, t_env *env)
{
	char			*temp;

	while (inp)
	{
		if (inp->infos == SEPA || inp->infos == NONE)
		{
			temp = ft_strdup(inp->cont);
			temp = line_env_interpret(temp, env);
			exec_cli(temp, env);
			free(temp);
		}
		else if (inp->infos == PIPE)
			printf("a\n");;
		if (inp->infos == NONE)
			break;
		inp = inp->next;
	}
}
