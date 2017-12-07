#include "hmini.h"

unsigned int		k_arrows_skipwd(char *scribe, unsigned int cursor,
						int left)
{
	unsigned int	i;
	unsigned int	shift;
	int				directio;

	i = cursor;
	shift = 0;
	directio = left ? -1 : 1;
	if (scribe[cursor] && scribe[cursor] <= 32)
		while (((scribe[i] && !left) || (i && left)) && scribe[i] <= 32)
		{
			i += directio;
			shift++;
		}
	while (((scribe[i] && !left ) || (i && left)) && scribe[i] > 32)
	{
		i += directio;
		shift++;
	}
	write(1, "\033[", 2);
	ft_putnbr(shift);
	left ? write(1, "D", 1) : write(1, "C", 1);
	return (cursor + (shift * directio));
}
