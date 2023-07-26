/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:22:49 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/26 14:16:38 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lstnew_cmd(char **content)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->in = 0;
	node->out = 1;
	node->data = content;
	node->next = NULL;
	return (node);
}

void	lstaddback_cmd(t_cmd *new)
{
	t_cmd	*node;

	if (g_all.cmd == NULL)
	{
		g_all.cmd = new;
		return ;
	}
	node = g_all.cmd;
	while (node->next)
		node = node->next;
	node->next = new;
}

int	ft_count(t_nodes *node)
{
	int	count;

	count = 0;
	while (node && node->type != PIPES)
	{
		if (node && node->type < 5 /*&& node->valeur[0]*/)
			count++;
		node = node->next;
	}
	return (count);
}

void	fill_data(t_nodes **node, char **data)
{
	int	i;

	i = 0;
	while ((*node) && (*node)->type != PIPES)
	{
		if ((*node) && (*node)->type < 5 /*&& (*node)->valeur[0]*/)
			data[i++] = ft_strdup((*node)->valeur);
		(*node) = (*node)->next;
	}
	data[i] = NULL;
	lstaddback_cmd(lstnew_cmd(data));
}

void	pipe_node(t_env *env)
{
	t_nodes	*node;
	char	**data;
	int		count;

	count = 0;
	node = g_all.head;
	while (node)
	{
		count = ft_count(node);
		data = malloc(sizeof(char **) * (count + 1));
		if (!data)
			return ;
		fill_data(&node, data);
		if (node)
			node = node->next;
	}
	redirect(g_all.cmd, env);
}
