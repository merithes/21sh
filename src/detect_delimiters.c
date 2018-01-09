/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_delimiters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:38:52 by vboivin           #+#    #+#             */
/*   Updated: 2018/01/09 19:32:46 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

int					check_separator_microscale(char *inp, char *to_check)
{
	long long int	i;
	char			*tmp;

	if (!ft_strcmp(inp, to_check))
		return (0);
	if ((tmp = ft_strstr(inp, to_check)) != NULL)
	{
		i = tmp - inp;
		if (i <= 0 || inp[i - 1] == '\\')
			return (0);
		return (1);
	}
	return (0);
}

int					contains_delims(char *inp)
{
	if (inp[0] != '\"' || inp[0] != '\'')
	{
		if (check_separator_microscale(inp, ";") ||
			check_separator_microscale(inp, "|") ||
			check_separator_microscale(inp, "&") ||
			check_separator_microscale(inp, "||") ||
			check_separator_microscale(inp, "&&"))
			return (1);
	}
	return (0);
}

int					check_separators_bigscale(char **inp)
{
	int				i;

	i = -1;
	while (inp[++i])
		if (contains_delims(inp[i]))
			return (1);
	return (0);
}

char				**recompress_lst(t_list *lst)
{
	char			**outp;
	int				len;
	t_list			*cursor;

	len = 0;
	cursor = lst;
	if (!(outp = malloc(sizeof(char *) * (len + 1))))
		ft_error(MAF, -1);
	//ADD ACTUAL RECOMPRESSION HERE============================================
	return (outp);
}

int					detect_bad_delimiters(char ***inp)
{
	t_list			*list;

	if (!check_separators_bigscale(*inp))
		return (0);
	list = convert_inp_lst(*inp);
	free(*inp);
	*inp = recompress_lst(list);
	return (0);
}

int					detect_delimiters(char **inp)
{
	int				i;

	i = -1;
	while (inp[++i] != NULL)
	{
		if (!ft_strcmp("|", inp[i]))
			return (1);
		else if (!ft_strcmp(";", inp[i]))
			return (1);
		else if (!ft_strcmp("||", inp[i]))
			return (1);
		else if (!ft_strcmp("&&", inp[i]))
			return (1);
	}
	return (0);
}
