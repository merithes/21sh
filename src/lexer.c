/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 15:04:28 by vboivin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/02 12:08:49 by jamerlin         ###   ########.fr       */
=======
/*   Updated: 2018/01/30 18:59:23 by vboivin          ###   ########.fr       */
>>>>>>> aaca760f23950ea7bfb5614ffc7b17cc026bd5f2
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

int					redir_is_valid(char *inp)
{
	int				i;

	//WONT WORK UNTIL CORRECT DELIMS SUCH AS "ls dir>truc"
	//ARE DISCRIMINATED FROM REDIRS SUCH AS "ls 2>truc"
	//(first example must be splitted as "dir > truc" or "dir >truc")
	i = 0;
	printf("a\t%s\n", inp);
	while (inp[i] >= '0' && inp[i] <= '9')
		i++;
	printf("b\t%s\n", inp);
	if (inp[i] != '>' && inp[i] != '<')
		return (1);
	i++;
	printf("c\t%s\n", inp);
	if (inp[i] == inp[i - 1])
		i++;
	printf("d\t%s\n", inp);
	if (inp[i] == '&')
	{
		i++;
		if (inp[i] == '-')
			;
		else if (inp[i] >= '0' && inp[i] <= '9')
		{
			while (inp[i] >= '0' && inp[i] <= '9')
				i++;
			if (inp[i] != 0)
				return (1);
		}
	}
	else if (contains_redir(inp + i))
		return (1);
	printf("e\t%s\n", inp);
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
			else if (redir_is_valid(inp[i]) != 0)
				return (ERR_4);
		}
	}
	return (0);
}
