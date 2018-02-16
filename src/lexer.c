/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:04:28 by vboivin           #+#    #+#             */
/*   Updated: 2018/02/12 13:47:58 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

short int			is_delim(char *inp)
{
	int				len;

	if (!inp)
		return (0);
	len = ft_strlen(inp);
	if (len > 2)
		return (0);
	if (!ft_strcmp("||", inp) || !ft_strcmp("&&", inp) ||
		!ft_strcmp(";", inp) || !ft_strcmp("|", inp) || !ft_strcmp("&", inp))
		return (1);
	else if (!ft_strcmp(">>", inp) || !ft_strcmp("<<", inp)
		|| !ft_strcmp(">", inp) || !ft_strcmp("<", inp))
		return (2);
	return (0);
}

short int			req_next(char *inp)
{
	if (ft_strcmp("||", inp) || ft_strcmp("&&", inp) || ft_strcmp("|", inp) ||
		ft_strcmp(">>", inp) || ft_strcmp("<<", inp) || ft_strcmp(">", inp) ||
		ft_strcmp("<", inp))
		return (1);
	return (0);
}

int					contains_redir(char *inp)
{
	int				i;

	i = -1;
	while (inp[++i])
	{
		if (inp[i] == '\\')
			;
		else if (inp[i] == '>' || inp[i] == '<')
			return (1);
	}
	return (0);
}

int					redir_req_next(char *inp)
{
	int				i;

	i = 0;
	while (inp[i] != '<' && inp[i] != '>')
		i++;
	if (inp[i + 1] == inp[i])
		i++;
	if (!inp[i + 1])
		return (1);
	return (0);
}

int					lex_splitted(char **inp)
{
	int				i;

	i = -1;
	if (!inp)
		return (0);
	while (inp[++i])
	{
		if (inp[i][0] == '\'' || inp[i][0] == '\"')
			;
		else if (is_delim(inp[i]))
		{
			if (req_next(inp[i]) && (!inp[i + 1] || is_delim(inp[i + 1])))
				return (ERR_1);
		}
		else if (contains_redir(inp[i]))
		{
			if (redir_req_next(inp[i])&&
				(!inp[i + 1] || is_delim(inp[i + 1]) ||
				contains_redir(inp[i + 1])))
				return (inp[i + 1] ? ERR_2 : ERR_3);
		}
	}
	return (0);
}
