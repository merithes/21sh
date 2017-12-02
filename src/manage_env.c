/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:29:04 by vboivin           #+#    #+#             */
/*   Updated: 2017/10/21 21:53:41 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hmini.h"

char				*get_cut_env(char *inp, int type)
{
	char			*outp;
	int				len;

	if (!inp)
		return (NULL);
	len = (type) ? (int)ft_strlen(ft_strrchr(inp, '=') + 1) :
					(int)(inp - ft_strrchr(inp, '='));
	if (!(outp = malloc(len + 1)))
		return (NULL);
	outp = (type) ? ft_strdup(ft_strrchr(inp, '=') + 1) :
					ft_strndup(inp, len);
	return (outp);
}

t_env				*get_env_var(char *to_search, t_env *list)
{
	!(list->name) ? list = list->next : NULL;
	while (list)
	{
		if (ft_strcmp(to_search, list->name))
			list = list->next;
		else
			return (list);
	}
	return (NULL);
}

int					env_is_valid(char *name, char *cont)
{
	int				i;

	i = -1;
	if (!name || ((name[0] < 'A' || name[0] > 'Z') && name[0] != '_'))
		return (-1);
	while (name[++i])
		if ((name[i] < 'A' || name[i] > 'Z') && name[i] != '_'
				&& (name[i] < '0' || name[i] > '9'))
			return (-1);
	i = -1;
	if (cont)
		while (cont[++i])
			if (cont[i] == '=')
				return (-1);
	return (0);
}

char				*ft_var_brackets(char *str, int allc)
{
	int				i[2];
	char			*tmp;

	i[0] = -1;
	i[1] = 0;
	if (!str)
		return (NULL);
	while (str[++i[0]])
		(str[i[0]] == '"') ? i[1]++ : 1;
	if (i[1] && i[1] != 2)
	{
		allc ? free(str) : 1;
		return (NULL);
	}
	else if (i[1] == 2)
	{
		if (str[0] != '"' || str[ft_strlen(str) - 1] != '"')
			return (allc) ? return_free(str) : (NULL);
		i[1] = (int)ft_strlen(str);
		tmp = (ft_strndup(str + 1, (int)(ft_strlen(str) - 2)));
		return (allc) ? (return_free(str)) : (tmp);
	}
	return (str);
}
