/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:20:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 18:16:33 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void	lstclear_env(void)
{
	t_env	*tmp;
	t_env	*tmp_next;

	if (!g_all.env)
		return ;
	tmp = g_all.env;
	while (tmp)
	{
		tmp_next = tmp->next;
		free (tmp->s);
		free (tmp);
		tmp = tmp_next;
	}
	g_all.env = NULL;
}

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
