/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:35:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/09 12:13:03 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_link()
{
    int i;
    t_nodes *node;
    t_nodes *first;

    i = 0;
    node = g_all.head;
    while (node != NULL)
    {
        if (node->quotes != 0)
        {
            if (!i)
                first = node;            
            else
            {
                first->valeur = ft_strjoin(first->valeur, node->valeur);
                first->next = node->next;
                free(node->valeur);
                free(node);
                node = first;
            }
            i++;
        }
        node = node->next;
    }
    printf("\tfirst val : %s\n", first->valeur);
}