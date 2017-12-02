/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env_cli.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:27:40 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/23 07:24:53 by vboivin          ###   ########.fr       */
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

char				*new_str_cli(char *inp, t_env *env)
{
	size_t			i[3];
	char			*outp;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (inp[i[0]])
	{
		if (inp[i[0]] == '$')
		{
			i[2] = ft_pathlen(inp + i[0] + 1);
			i[1] += ft_strlen(get_env_cont(inp + i[0] + 1, i[2], env));
			i[0] += i[2] + 1;
		}
		else
			i[0]++;
	}
	if (!(outp = ft_strnew(i[0] + i[1])))
		return (NULL);
	return (outp);
}

char				*line_env_interpret(char *inp, t_env *env)
{
	char			*chars[2];
	int				i[4];

	if (!env || !inp || (!ft_strrchr(inp, '$') && !ft_strrchr(inp, '"'))
			|| (!(chars[0] = new_str_cli(inp, env))))
		return (inp);
	ft_bzero(i, sizeof(int) * 4);
	while (inp[i[0] + i[3]])
	{
		if (inp[i[0] + i[3]] != '$')
			chars[0][i[0] + i[1]] = inp[i[0] + i[3]];
		else
		{
			i[2] = ft_pathlen(inp + i[0] + i[3] + 1);
			if ((chars[1] = get_env_cont(inp + i[0] + i[3] + 1, i[2], env)))
				ft_strcat(chars[0], chars[1]);
			i[1] += (chars[1] != NULL) ? (int)ft_strlen(chars[1]) - 1 : -1;
			i[3] += (chars[1] != NULL) ? i[2] : i[2] + 1;
		}
		i[0]++;
	}
	free(inp);
	return (chars[0]);
}
