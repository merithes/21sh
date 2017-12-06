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
		while (scribe[i] && scribe[i] <= 32)
		{
			i += directio;
			shift++;
		}
	while (scribe[i])
	{
		
	}
}
