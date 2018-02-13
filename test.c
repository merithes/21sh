#include "libft.h"
#include <stdio.h>

int main(void)
{
	int		i;
	char	**ez;

	ez = ft_strsplit("sedqvf>zeg>>efzrfrzqae", '>');
	i = -1;
	printf("splitting \"sedqvf>zeg>>efzrfrzqae\" over '>'\n");
	while (ez[++i])
		printf("%d:\t|%s|\n", i, ez[i]);
}
