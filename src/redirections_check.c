/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:45:22 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/17 17:56:56 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					bad_redir(char *inp)
{
	if (!inp || inp[0] == '\'' || inp[0] == '\"' || !ft_strstr(inp, ">") ||
		!ft_strstr(inp, "<") || !ft_strstr(inp, ">>") || !ft_strstr(inp, "<<")
		|| !ft_strcmp(inp, ">") || !ft_strcmp(inp, "<") || !ft_strcmp(inp, ">>")
		|| !ft_strcmp(inp, "<<"))
		return (0);

}

t_list				*check_redirs(t_list *inp)
{
	t_list			*cursor[2];

	if (!inp)
		return (inp);
	cursor[0] = bad_redir((char *)(inp->content)) ? re_redir(inp) : inp;
	cursor[1] = NULL;
	while (cursor->next)
	{
		if (bad_redir((char *)cursor->next->content))
			cursor->next = re_redir(cursor->next);
		cursor= cursor->next;
	}
}
