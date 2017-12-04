#include "hmini.h"

unsigned int		k_home_end(int kc, unsigned int current_posi, char *scribe)
{
	unsigned int	i;

	if (kc && current_posi) 
	{
		write(1, "\033[", 2);
		ft_putnbr(current_posi);
		write(1, "D", 1);
		return (0);
	}
	else if (!kc)
	{
		i = ft_strlen(scribe);
		if (i > current_posi)
		{
			write(1, "\033[", 2);
			ft_putnbr(i - current_posi);
			write(1, "C", 1);
		}
		return (i);
	}
	return (current_posi);
}
