#include "hmini.h"

void				exec_lst(t_listc *inp, t_env *env)
{
	int				i;
	char			*tmp;

	tmp = NULL;
//		printf("==========================================\n");
	while (inp)
	{
		if (inp->sep_type == SEPA || inp->sep_type == NONE)
		{
			i = -1;
			while (inp->cont[i] != NULL)
			{
				tmp = line_env_interpret(inp->cont[i], env);
				free(inp->cont[i]);
				inp->cont[i] = tmp;
			}
//			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			exec_cli(inp->cont[0], inp, env);
		}
		else if (inp->sep_type == PIPE)
//			printf("a\n");
		if (inp->sep_type == NONE)
			break;
//			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		inp = inp->next;
	}
//			printf("::::::::::::::::::::::::::::::::::::::::::\n");
}
