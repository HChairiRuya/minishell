/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:54:33 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/19 18:02:01 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void	ft_lstaddback(t_nodes *node, t_nodes *new)
{
	if (!node || !new)
		return ;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	lstaddback_save(t_nodes **node, t_nodes *new)
{
	if (!node || !new)
		return ;
	if (*node)
		ft_lstlast(*node)->next = new;
	else
		*node = new;
}

void	g_all_clear_cmd(void)
{
	t_cmd	*tmp;
	int		i;
	t_cmd	*tmp_next;

	if (!g_all.cmd)
		return ;
	tmp = g_all.cmd;
	while (tmp)
	{
		i = -1;
		tmp_next = tmp->next;
		while (tmp->data[++i])
			free (tmp->data[i]);
		free (tmp->data);
		free (tmp);
		tmp = tmp_next;
	}
	g_all.cmd = NULL;
}

void	g_all_clear(void)
{
	t_nodes	*tmp;
	t_nodes	*tmp_next;

	if (!g_all.head)
		return ;
	tmp = g_all.head;
	while (tmp)
	{
		tmp_next = tmp->next;
		free (tmp->valeur);
		free (tmp);
		tmp = tmp_next;
	}
	g_all.head = NULL;
}


void	lstclear_env(t_env *node)
{
	t_env	*tmp;
	t_env	*tmp_next;

	if (!node)
		return ;
	tmp = node;
	while (tmp)
	{
		tmp_next = tmp->next;
		free (tmp->s);
		free (tmp);
		tmp = tmp_next;
	}
	node = NULL;
}


t_nodes	*ft_lstlast(t_nodes *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
