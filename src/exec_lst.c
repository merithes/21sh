#include "hmini.h"

void				exec_lst(t_listc *inp, t_env *env)
{
	int i = 0;
	int	p[2];
	pid_t father = 0;

	/*int i; // verification des maillons
	t_listc *beg;

	i = 0;
	beg = inp;
	while (beg)
	{
		printf("%s\n", beg->cont[0]);
		beg = beg->next;
	}*/
	while (inp)
	{
		if (inp->sep_type == SEPA || inp->sep_type == NONE)
			exec_cli(inp->cont[0], inp, env);
		else if (inp->sep_type == PIPE)
		{
			prepare_pipe(inp);
			do_pipe(inp, 0, father, p);
			while (i < inp->nb_arg - 1)
			{
				inp = inp->next;
				i++;
			}
		}
			//exec_cli(inp->cont[0], inp, env); //juste un test
			//printf("check src/exec_lst.c to add PIPE exec interpreter for %s\n",
			//		inp->cont[0]);
		else if (inp->sep_type == BCKG)
			printf("check src/exec_lst.c to add BCKG exec interpreter for %s\n",
					inp->cont[0]);
		else if (inp->sep_type == AND)
			printf("check src/exec_lst.c to add AND exec interpreter for %s\n",
					inp->cont[0]);
		else if (inp->sep_type == OR)
			printf("check src/exec_lst.c to add OR exec interpreter for %s\n",
					inp->cont[0]);
		if (inp->sep_type == NONE)
			break;
		inp = inp->next;
	}
}
