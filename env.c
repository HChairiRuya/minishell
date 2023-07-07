/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:20:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/06 14:51:04 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(char *content)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->s = ft_strdup(content);
	node->next = NULL;
	return (node);
}


void	ft_lstaddback2(t_env **node, t_env *new)
{
	if (*node == NULL)
	{
		*node = new;
		return ;
	}
	while ((*node)->next)
		node = &(*node)->next;
	(*node)->next = new;
}

void	save_env(t_env **node, char **envr)
{
	int i;

	i = 0;
	// node = NULL;
	while (envr[i])
	{
		ft_lstaddback2(node, ft_lstnew(envr[i]));
		i++;
	}
	// pour voir env in linked list
	// t_env *curr = node;
	// while (curr)
	// {
	// 	 printf("[%s]\n", curr->s);
	// 	 curr = curr->next;
	// }
}