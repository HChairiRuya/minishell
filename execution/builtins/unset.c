/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 16:28:55 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

// t_env	*to_unset(t_env *env_list, char *arg)
// {
// 	t_env	*node;
// 	t_env	*head;

// 	head = NULL;
// 	node = g_all.env;
// 	while (node != NULL)
// 	{
// 		if (!ft_strncmp(node->s, arg, ft_strlen(arg)))
// 		{
// 			if (head == NULL)
// 			{
// 				g_all.env = g_all.env->next;
// 				return (g_all.env);
// 			}
// 			else
// 				head->next = node->next;
// 			return (node);
// 		}
// 		head = node;
// 		node = node->next;
// 	}
// 	return (NULL);
// }

void	to_unset(t_env *env, char *arg)
{
	t_env	*tmp;
	
	tmp = NULL;
	while (env)
	{
		if(!ft_strncmp(env->s, arg, ft_strlen(arg)))
		{
			if (tmp)
				tmp->next = env->next;
			else
				g_all.env = g_all.env->next;
			free(env->s);
			env->s = NULL;
			free(env);
			env = NULL;
			break ;
		}
		tmp = env;
		env = env->next;
	}
}

void	unset_node(t_env *node)
{
	if (node != NULL)
	{
		free(node->s);
		free(node);
	}
}

void	ft_unset(char **argv, t_env **env_list)
{
	// t_env	*node;
	int		i;

	i = 1;
	while (argv[i])
	{
		to_unset(*env_list, argv[i]);
		// unset_node(node);
		i++;
	}
}
