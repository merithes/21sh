#include "libft.h"

int					count_char(char *inp, char c)
{
	int				cnt;

	if (!inp)
		return (0);
	while (*inp)
	{
		if (*inp == c)
			cnt++;
		inp++;
	}
	return (cnt);
}
