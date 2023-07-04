/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:20:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/04 18:05:44 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_lstnew(char *content)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->s = ft_strdup(content);
	node->next = NULL;
	return (node);
}


void	ft_lstaddback2(t_node **node, t_node *new)
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

void	creer_nodes(t_node **node, char **envr)
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
	// t_node *curr = node;
	// while (curr)
	// {
	// 	 printf("[%s]\n", curr->s);
	// 	 curr = curr->next;
	// }
}

// char* getNodeValue(t_node* head, char* var) 
// {
//     t_node* current = head;
    
//     while (current != NULL) 
//     {
//         if (ft_strcmp(current->s, var) == 0)
//             return (current->s);
//         current = current->next;
//     }
//     return (NULL);
// }



// void    save_env(t_node *node)
// {
    
// }