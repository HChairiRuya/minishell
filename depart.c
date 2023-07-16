/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depart.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:46:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/16 18:24:01 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_list(char *valeur, int type)
{
	t_nodes	*node;

	node = malloc(sizeof(t_nodes));
	if (!node)
	{
		// free(node);
		free(valeur);
		return ;
	}
	node->next = NULL;
	node->quotes = 0;
	node->type = type;
	node->valeur = ft_strdup(valeur);
	if (!g_all.head)
		g_all.head = node;
	else
		ft_lstaddback(g_all.head, node);
	free(valeur);
}

void	rm_spaces(void)
{
	t_nodes	*node;

	node = g_all.head;
	while (node != NULL)
	{
		if (node == g_all.head && node->type == SPACES && node->quotes == 0)
		{
			while (node && node->type == SPACES)
				free_space(&node);
		}
		if ((node && node->next && node->next->type == SPACES
				&& node->next->quotes == 0))
		{
			node = node->next;
			while (node->next && node->next->type == SPACES)
				free_node_exp(node);
		}
		if (node)
			node = node->next;
	}
}

void	split_function(void)
{
	char	*s;

	s = g_all.line;
	while (*s)
	{
		if (*s == ' ')
			spaces(&s);
		else if (*s == '$')
			dollar(&s);
		else if (*s == '|')
			pipes(&s);
		else if (*s == '\"')
			double_quotes(&s);
		else if (*s == '\'')
			single_quotes(&s);
		else if (*s == '<' || *s == '>')
			redirections(&s);
		else
			string(&s);
	}
	check_nodes();
	rm_spaces();
}
