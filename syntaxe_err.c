/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:06:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/09 19:46:54 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   next_node(t_nodes *node)
{
    if ((node->type == RED_IN || node->type == RED_OUT 
        || node->type == APPEND || node->type == HERDOC 
        || node->type == PIPES))
        return (1);
    return (0);
}


int syntaxe_err()
{
    t_nodes *node;

    node = g_all.head;
    if (node->type == PIPES)
        return (1);
    while (node != NULL && node->next != NULL)
    {
        if (node->type == RED_IN && next_node(node->next->next))
            return (1);
        if (node->type == RED_OUT && next_node(node->next->next))
            return (1); 
        if (node->type == PIPES && node->next->next->type == PIPES)
            return (1);
        if (node->type == APPEND && next_node(node->next->next))
            return (1);
        if (node->type == HERDOC && next_node(node->next->next))
            return (1);
        if (node->type == S_ERR)
            return (1);
        node = node->next;
    }
    if (node->type == PIPES ||node->type == RED_IN || node->type == RED_OUT || node->type == APPEND || node->type == HERDOC || node->type == S_ERR)
        return (1);
    return (0);
}