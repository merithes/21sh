/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env_cli.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:27:40 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/08 14:08:22 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*get_env_cont(char *inp, size_t size, t_env *env)
{
	char			tmp[size + 1];
	t_env			*cursor;

	ft_bzero(tmp, size + 1);
	ft_strncpy(tmp, inp, size);
	if (!(cursor = get_env_var(tmp, env)))
		return (NULL);
	return (cursor->cont);
}

char				*line_env_interpret(char *inp, t_env *env)
{
	char			*chars[2];

	if (!env || !inp || (!ft_strrchr(inp, '$') && !ft_strrchr(inp, '"')
			&& !ft_strrchr(inp, '\'')))
		return (NULL);
	if (inp[0] == '\'')
		interpret_quotes(inp, env, 0);
	else if (inp[0] == '"')
		interpret_quotes(inp, env, 1);
	else
		interpret_nquotes;
}
