#include "hmini.h"

t_list				*filter_redirs(t_list *inp, int typ)
{
	char			*workon;
	int				cnt;
	t_list			*outp;

	if (!inp->content)
		return (typ ? inp->next : inp);
	if (ft_strstr(inp->content, ">>") != inp->content &&
		ft_strlen(inp->content) > 2)
		return (split_dbright(inp));
	if (ft_strstr(inp->content, "<<") != inp->content &&
		ft_strlen(inp->content) > 2)
		return (split_dbleft(inp));
// EDIT MODIFY CHANGE HERE
}

t_list				*check_redirs(t_list *inp)
{
	t_list			*cursor;

	if (!inp)
		return (inp);
	cursor = filter_redirs(inp, 0);
	while (inp->next)
	{
		if (!inp->content || inp->content[0] == '\"' || inp->content[0] == '\'')
			inp = inp->next;
		else if (ft_strcmp(inp->content, ">") && ft_strcmp(inp->content, "<"))
		{
			inp->next = filter_redirs(inp->next, 1);
		else
			inp = inp->next;
	}
}
