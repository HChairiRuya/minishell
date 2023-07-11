/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:06:01 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/11 20:10:35 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int   next_node(t_nodes *node)
{
    if (node->type == STRING)
        return(0);
    if (node->type == SPACES && !node->next)
        return (1);
    node = node->next;
    if (node && (node->type == RED_IN || node->type == RED_OUT 
        || node->type == APPEND || node->type == HERDOC
        || node->type == PIPES))
        return (1);
    return (0);
}


int ft_pipe(t_nodes *node)
{
    if (node->quotes == 0 && node->type == PIPES)
    {
        node = node->next;
        while (node)
        {
            if (node->quotes == 0 && node->type == PIPES)
                return (1);
            if ((node->quotes == 0 && node->type != PIPES))
                return (0);
            node = node->next;
        }
    }
    return (0);
}

int    quotes(t_nodes *node)
{
    int d;
    int s;

    d = 0;
    s = 0;
    while (node)
    {
        if (node && node->quotes == 0 && node->type == DOUBLES_QUOTES)
            d++;
        if (node && node->quotes == 0 && node->type == SINGLE_QUOTES)
            s++;
        node = node->next;
    }
    if (d % 2 != 0 || s % 2 != 0)
        return (1);
    return (0);
}


int syntaxe_err()
{
    t_nodes *node;

    node = g_all.head;
    if (node && (node->type == PIPES || quotes(node)))
        return (1);
    while (node != NULL && node->next != NULL)
    {
        if (node->quotes == 0 && node->type == RED_IN && next_node(node->next))
            return (1);
        if (node->quotes == 0 && node->type == RED_OUT && next_node(node->next))
            return (1); 
        if (node->quotes == 0 && node->type == APPEND && next_node(node->next))
            return (1);
        if (node->quotes == 0 && node->type == HERDOC && next_node(node->next))
            return (1);
        if (ft_pipe(node))
            return (1);
        if (node->quotes == 0 && node->type == S_ERR)
            return (1);
        node = node->next;
    }
    if (node && (node->type == PIPES || node->type == RED_IN || node->type == RED_OUT
        || node->type == APPEND || node->type == HERDOC || node->type == S_ERR))
        return (1);
    return (0);
}