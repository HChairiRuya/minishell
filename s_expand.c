/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:48:13 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/14 18:54:06 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space(char *value)
{
	int	i;

	i = 0;
	if (!value)
		return (0);
	while (value[i])
	{
		if (value[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	save_list(t_nodes **node, char *val)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(val, ' ');
	while (tab[i])
	{
		lstaddback_save(node, lstnew_expand(tab[i]));
		i++;
	}
	i = 0;
	while (tab[i++])
	    free(tab[i]);
	free(tab);
}

int	char_special(int c)
{
	if (c == '-' || c == '+' || c == '/' || c == '^'
		|| c == '%' || c == '.' || c == ',' || c == '=')
		return (1);
	return (0);
}
