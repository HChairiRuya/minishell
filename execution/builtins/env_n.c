/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:30:58 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 14:55:15 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int	is_valid(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '_' && !ft_isalpha(s[i]))
		return (1);
	while (s[++i] && s[i] != '=')
	{
		if (s[i] != '_' && !ft_isalnum(s[i]))
			return (1);
	}
	return (0);
}

void	add_node_to_env(t_env *env, char *s)
{
	t_env	*new_node;
	t_env	*last;

	new_node = ft_lstnew(s);
	if (new_node)
	{
		if (env == NULL)
			g_all.env = new_node;
		else
		{
			last = env;
			while (last->next != NULL)
				last = last->next;
			last->next = new_node;
		}
	}
}

void	pr_env(t_env *env)
{
	while (env != NULL)
	{
		if (ft_strchr(env->s, '='))
			printf("%s\n", env->s);
		env = env->next;
	}
}
