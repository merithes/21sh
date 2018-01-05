#include <stdio.h>

char				**splitter_alt(char *inp);

int					main(int ac, char *av[])
{
	int				i;
	char			**tmp;

	i = -1;
	tmp = splitter_alt("truca \";\" ; trucb");
	while (tmp[++i])
		printf("%s\n", tmp[i]);
}
