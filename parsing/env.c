/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:20:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/19 17:55:50 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

t_env	*ft_lstnew(char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->s = ft_strdup(content);
	node->next = NULL;
	return (node);
}

t_nodes	*lstnew_expand(char *content)
{
	t_nodes	*node;

	node = malloc(sizeof(t_nodes));
	if (!node)
		return (NULL);
	node->type = EXPANDED;
	node->quotes = 0;
	node->valeur = ft_strdup(content);
	node->next = NULL;
	return (node);
}

void	lstaddback_env(t_env **node, t_env *new)
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
	int	i;

	i = 0;
	while (envr[i])
	{
		lstaddback_env(node, ft_lstnew(envr[i]));
		i++;
	}
}
