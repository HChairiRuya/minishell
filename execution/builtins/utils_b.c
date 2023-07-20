/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:50:26 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/20 12:57:18 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

t_env *ft_lstnew(char *cont)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->s = ft_strdup(cont);
    node->next = NULL;
    return (node);
}

void ft_lstaddback(t_env **node, t_env *new)
{
    if (*node == NULL)
    {
        *node = new;
        return;
    }
    t_env *curr = *node;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
}

t_env *save_env_e()
{
    extern char **environ;
    char **env = environ;
    t_env *env_h = NULL;
    while (*env)
    {
        ft_lstaddback(&env_h, ft_lstnew(*env));
        env++;
    }
    return (env_h);
}