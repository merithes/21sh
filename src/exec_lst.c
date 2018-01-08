#include "hmini.h"

void				exec_lst(t_listc *inp, t_env *env)
{
	int				i;
	char			*tmp;

	tmp = NULL;
	while (inp)
	{
		if (inp->sep_type == SEPA || inp->sep_type == NONE)
		{
			i = -1;
			while (inp->cont[++i] != NULL)
			{
				if ((tmp = line_env_interpret(inp->cont[i], env)) != NULL)
				{
					free(inp->cont[i]);
					inp->cont[i] = tmp;
				}
			}
			exec_cli(inp->cont[0], inp, env);
		}
		else if (inp->sep_type == PIPE)
			printf("check src/exec_lst.c to add PIPE execution interpreter\n");
		if (inp->sep_type == NONE)
			break;
		inp = inp->next;
	}
}
