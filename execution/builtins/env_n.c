/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:30:58 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/19 18:08:47 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void pr_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->s);
        tmp = tmp->next;
    }
}

t_env *save_env_b()
{
    extern char **environ;
    char **env = environ;
    t_env *env_h = NULL;
    while (*env)
    {
        lstaddback_env(&env_h, ft_lstnew(*env));
        env++;
    }
    return (env_h);
}

void free_env(t_env *node)
{
    t_env *curr;
    while (node != NULL)
    {
        curr = node;
        node = node->next;
        free(curr->s);
        free(curr);
    }
}

void ft_env()
{
    t_env *env_l = save_env_b();
    pr_env(env_l);

    free_env(env_l);
}

