/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:30:58 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 17:03:51 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void add_node_to_env(t_env *env, char *s)
{
    t_env   *new_node;
    t_env   *last;
    
    new_node = ft_lstnew(s);
    if (new_node)
    {
        if (env == NULL)
            env = new_node;
        else
        {
            last = env;
            while (last->next != NULL)
                last = last->next;
            last->next = new_node;
        }
    }
}

void pr_env(t_env *env)
{
    while (env != NULL)
    {
        if (ft_strchr(env->s, '='))
            printf("%s\n", env->s);
        env = env->next;
    }
}

// void free_env(t_env *node)
// {
//     t_env *curr;
//     while (node != NULL)
//     {
//         curr = node;
//         node = node->next;
//         free(curr->s);
//         free(curr);
//     }
// }

