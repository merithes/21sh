#include "hmini.h"

t_listc				*create_chain_link(t_listc *prevv)
{
	t_listc			*outp;

	if (!(outp = malloc(sizeof(t_listc))))
		ft_error("Memory allocation failed.\n", -1);
	outp->prev = prevv;
	outp->next = NULL;
	outp->cont = NULL;
	outp->sep_type = 0;
	return (outp);
}

void				set_link(t_listc, char **cli)
{
	int				i;

	i = 0;
	while (cli[i]
}

void				craft_chain(t_listc *outp, char **cli)
{
	int				i;

	while (1)
	{
		set_link(outp, cli);
		if (outp->sep_type == NONE)
			break ;
		else
			outp->next = create_link_chain(outp);
	}
}

t_listc				*cut_string_delimiters(char **inp)
{
	t_listc			*outp;

//	printf("wuta\n");
	outp = create_chain_link(NULL);
//	printf("wut\n");
	craft_chain(outp, inp);
/*	while (outp)
	{
		printf("%d\t%s\n", outp->sep_type, outp->cont);
		outp = outp->next;
	}*/
	inp ? free(inp) : 0;
	return (outp);
}
