#include <hmini.h>

void				clear_scrn(char *scribe, unsigned int cursor)
{
	size_t			len;

	len = ft_strlen(scribe);
	write(1, "\033[2J\033[1;1H", 10);
	write_prompt(g_backup_env);
	ft_putstr(scribe);
	if (cursor != len)
		move_back((int)(len -cursor));
}
