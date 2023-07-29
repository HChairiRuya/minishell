/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 20:46:23 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

t_env	*to_unset(t_env *env_list, char *arg)
{
	t_env	*node;
	t_env	*head;

	head = NULL;
	node = env_list;
	while (node != NULL)
	{
		if (!ft_strncmp(node->s, arg, ft_strlen(arg)))
		{
			if (head == NULL)
				env_list = node->next;
			else
				head->next = node->next;
			return (node);
		}
		head = node;
		node = node->next;
	}
	return (NULL);
}

void	unset_node(t_env *node)
{
	if (node != NULL)
	{
		free(node->s);
		free(node);
	}
}

void	ft_unset(char **argv, t_env **env_list)
{
	t_env	*node;
	int		i;

	i = 1;
	while (argv[i])
	{
		node = to_unset(*env_list, argv[i]);
		unset_node(node);
		i++;
	}
}
