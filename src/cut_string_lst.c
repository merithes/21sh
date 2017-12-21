#include "hmini.h"

t_listc				*create_chain_link(void)
{
	t_listc			*outp;

	if (!(outp = malloc(sizeof(t_listc))))
		ft_error("Memory allocation failed.\n", -1);
	outp->prev = NULL;
	outp->next = NULL;
	outp->cont = NULL;
	outp->infos = 0;
	return (outp);
}

int					delim_finder(char *cli)
{
	int				i;

	i = -1;
	while (cli[++i])
	{
		if (cli[i] == '\\')
		{
			if (cli[i + 1] == '&' && cli[i + 2] != '&')
				i += 2;
			else if (cli[i + 1] == '&' && cli[i + 2] == '&')
				i += 3;
			else if (cli[i + 1] == ';')
				i += 2;
			else if (cli[i + 1] == '|')
				i += 2;
			else if (cli[i + 1] == '|' || cli[i + 2] == '|')
				i += 3;
		}
		if (cli[i] == '&')
			return (i);
		else if (cli[i] == '|')
			return (i);
		else if (cli[i] == ';')
			return (i);
	}
	return (i);
}

void				craft_chain(t_listc *outp, char *cli)



{
	int				i;

	while (cli[0])
	{
		i = delim_finder(cli);
		if (!(outp->cont = ft_strnew(i)))
			ft_error("Memory Allocation Failed.\n", -1);
		ft_strncpy(outp->cont, cli, i);
		if (cli[i] == ';')
			outp->infos = SEPA;
		else if (cli[i] == '|' && cli[i + 1] != '|')
			outp->infos = OR;
		else if (cli[i] == '&' && cli[i + 1] != '&')
			outp->infos = AND;
		else if (cli[i] == '|')
			outp->infos = PIPE;
		else if (cli[i] == '&')
			outp->infos = BCKG;
		outp->next = create_chain_link();
		outp->next->prev = outp;
		if (!outp->infos)
			break ;
		outp = outp->next;
		cli += i + 1;
	}
}

t_listc				*cut_string_delimiters(char *inp)
{
	t_listc			*outp;

//	printf("wuta\n");
	outp = create_chain_link();
//	printf("wut\n");
	craft_chain(outp, inp);
/*	while (outp)
	{
		printf("%d\t%s\n", outp->infos, outp->cont);
		outp = outp->next;
	}*/
	return (outp);
}
