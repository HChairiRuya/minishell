/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 22:43:38 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_unset(int argc, char **argv, t_env **env_list)
{
    t_env *head;
    t_env *node;
    int i = 1;

    while (i < argc)
    {
        head = NULL;
        node = *env_list;
        while (node != NULL)
        {
            if (ft_strncmp(node->s, argv[i], ft_strlen(argv[i])) == 0 /* node->s[ft_strlen(argv[i])] == '='*/)
            {
                if (head == NULL) // Node to remove is the first one
                {
                    *env_list = node->next;
                    free(node->s);
                    free(node);
                    node = *env_list;
                }
                else
                {
                    head->next = node->next;
                    free(node->s);
                    free(node);
                    node = head->next;
                }
                break; // No need to continue searching for this argument
            }
            head = node;
            node = node->next;
        }

        i++;
    }
}
