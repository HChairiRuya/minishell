/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:35:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/20 15:35:34 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_strings(void)
{
	t_nodes	*node;
	t_nodes	*first;

	node = g_all.head;
	while (node != NULL)
	{
		if (node->quotes != 0)
		{
			first = node;
			if (first->type != IN_FILE && first->type != OUT_FILE)
				first->type = STRING;
			node = node->next;
			while (node && node->quotes != 0)
			{
				first->valeur = ft_strjoin(first->valeur, node->valeur, 1);
				first->next = node->next;
				free(node->valeur);
				free(node);
				node = first->next;
			}
		}
		if (node)
			node = node->next;
	}
}

void	link_tous(void)
{
	t_nodes	*node;
	t_nodes	*first;

	node = g_all.head;
	while (node != NULL)
	{
		if ((!(node->type >= 4 && node->type <= 9) && node->type != PIPES))
		{
			first = node;
			node = node->next;
			while (node && ((!(node->type >= 4 && node->type <= 9)
						&& node->type != PIPES)))
			{
				first->valeur = ft_strjoin(first->valeur, node->valeur, 1);
				first->next = node->next;
				free(node->valeur);
				free(node);
				node = first->next;
			}
		}
		if (node)
			node = node->next;
	}
}

void	print_data(void)
{
	t_cmd	*node;
	int		i;

	node = g_all.cmd;
	while (node)
	{
		i = 0;
		while (node->data[i])
		{
			printf("\tdata[%d] : %s\n", i, node->data[i]);
			i++;
		}
		printf("\tCMD IN : %d\n", node->in);
		printf("\tCMD OUT : %d\n", node->out);
		node = node->next;
	}
}
