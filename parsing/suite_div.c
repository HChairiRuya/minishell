/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suite_div.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:07:06 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/14 19:22:56 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(char *valeur)
{
	if (!ft_strcmp(valeur, "<"))
		return (RED_IN);
	else if (!ft_strcmp(valeur, "<<"))
		return (HERDOC);
	else if (!ft_strcmp(valeur, ">"))
		return (RED_OUT);
	else if (!ft_strcmp(valeur, ">>"))
		return (APPEND);
	else
		return (S_ERR);
}

void	redirections(char **s)
{
	char	*valeur;
	int		len;

	if (**s == '<' || **s == '>')
	{
		len = 0;
		while (**s && (**s == '<' || **s == '>'))
		{
			len++;
			(*s)++;
		}
		if (len)
		{
			valeur = ft_substr(*s - len, 0, len);
			create_list(valeur, check_redirect(valeur));
		}
	}
}

void	string(char **s)
{
	int		len;
	char	*valeur;

	len = 0;
	while (**s && !ft_strchr("<>| $", **s) && (**s != '\'' && **s != '\"'))
	{
		len++;
		(*s)++;
	}
	if (len)
	{
		valeur = ft_substr(*s - len, 0, len);
		create_list(valeur, STRING);
	}
}
