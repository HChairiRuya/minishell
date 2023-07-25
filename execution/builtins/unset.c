/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 11:50:22 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

// void	remove_nodes(t_env **node, char **argv, int i, t_env **env_list)
// {
// 	t_env	*head;
	
// 	while (node != NULL)
// 	{
// 		if (ft_strncmp((*node)->s, argv[i], ft_strlen(argv[i])) == 0 /* (*node)->s[ft_strlen(argv[i])] == '='*/)
// 		{
// 			if ((*node) == *env_list) // (*Node) to remove is the first one
// 			{
// 				*env_list = (*node)->next;
// 				free((*node)->s);
// 				free((*node));
// 				(*node) = *env_list;
// 			}
// 			else
// 			{
// 				head = (*node)->next;
// 				free((*node)->s);
// 				free(*node);
// 				(*node) = head;
// 			}
// 			break; // No need to continue searching for this argument
// 		}
// 		(*node) = (*node)->next;
// 	}
// }

// void	ft_unset(char **argv, t_env **env_list)
// {
// 	t_env	*node;
// 	int		i;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		node = *env_list;
// 		remove_nodes(&node, argv, i, env_list);
// 		i++;
// 	}
// }

t_env	*to_unset(t_env *env_list, char *arg)
{
    t_env *node;
    t_env *head;
	
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

void unset_node(t_env* node)
{
    if (node != NULL) 
	{
        free(node->s);
        free(node);
    }
}

void ft_unset(char **argv, t_env **env_list)
{
	t_env *node;
    int i = 1;

    while (argv[i])
	{
        node = to_unset(*env_list, argv[i]);
        unset_node(node);
        i++;
    }
}
