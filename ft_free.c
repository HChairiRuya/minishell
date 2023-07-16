/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:58:43 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/13 21:31:04 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_space(t_nodes **head)
{
	t_nodes	*tmp;

	tmp = g_all.head;
	g_all.head = g_all.head->next;
	free(tmp->valeur);
	free(tmp);
	*head = g_all.head;
}

void	free_node_exp(t_nodes *head)
{
	t_nodes	*tmp;

	tmp = head->next; // node qui existe apres $ 
	head->next = head->next->next;
	free(tmp->valeur);
	free(tmp);
}

void	delete_node_expanded(t_nodes *del, t_nodes *save)
{
	t_nodes	*tmp;

	tmp = g_all.head;
	if (del == tmp)
	{
		g_all.head = save;
		free(tmp->valeur);
		free(tmp);
	}
	else
	{
		while (tmp->next != del)
			tmp = tmp->next;
		tmp->next = save;
	}
	if (del->next)
	{
		free(del->next->valeur);
		free(del->next);
	}
	free(del->valeur);
	free(del);
}
