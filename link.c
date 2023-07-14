/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:35:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/14 15:31:49 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    link_strings()
{
    t_nodes *node;
    t_nodes *first;

    node = g_all.head;
    while (node != NULL)
    {
        if (node->quotes != 0)
        {
            first = node;
            first->type = STRING;
            node = node->next;
            while (node && node->quotes != 0)
            {  
                first->valeur = ft_strjoin(first->valeur, node->valeur);
                first->next = node->next;
                free(node->valeur);
                free(node);
                node = first->next;
            }
            // if (node->next && node->next->type != SPACES)
            // {
            //     first->valeur = ft_strjoin(first->valeur, node->valeur);
            //     first->next = node->next;
            //     free(node->valeur);
            //     free(node);
            //     node = first->next;
            // }
        }
        if (node)
            node = node->next;
    }
}

void    link_tous()
{
    t_nodes *node;
    t_nodes *first;
    
    node = g_all.head;
    while (node != NULL)
    {
        if ((!(node->type >= 4 && node->type <= 9) && node->type != PIPES))
        {
            first = node;
            node = node->next;
            while (node && ((!(node->type >= 4 && node->type <= 9) && node->type != PIPES)))
            {
                first->valeur = ft_strjoin(first->valeur, node->valeur);
                first->next = node->next;
                free(node->valeur);
                free(node);
                node = first->next;
            }
        }
        if (node)
            node = node->next;
    }
}


t_cmd	*lstnew_cmd(char **content)
{
	t_cmd   *node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->data = content;
	node->next = NULL;
	return (node);
}

void	lstaddback_cmd(t_cmd *new)
{
    t_cmd   *node;

	if (g_all.cmd == NULL)
	{
		g_all.cmd = new;
		return ;
	}
    node = g_all.cmd;
	while (node->next)
		node = node->next;
	node->next = new;
}

int ft_count(t_nodes *node)
{
    int count;

    count = 0;
    while (node && node->type != PIPES)
    {
        if (node && node->type < 5 && node->valeur[0])
            count++;
        node = node->next;
    }
    return (count);
}     

void    pipe_node()
{
    t_nodes *node;
    char    **data;
    int     count;
    int     i;

   
    count = 0;
    node = g_all.head;
    while (node)
    {
        i = 0;
        count = ft_count(node);
        data = malloc(sizeof(char **) * (count + 1));
        if (!data)
            return ;
        while (node && node->type != PIPES)
        {
            if (node && node->type < 5 && node->valeur[0])
                data[i++] = ft_strdup(node->valeur);
            node = node->next;
        }
        data[i] = NULL;
        lstaddback_cmd(lstnew_cmd(data));
        if (node)
            node = node->next;
    }
}

void    print_data()
{
    t_cmd *node;
    int i;
    

    node = g_all.cmd;
    while(node)
    {
        i = 0;
        while (node->data[i])
        {
            printf("\tdata[%d] : %s\n", i, node->data[i]);
            i++;
        }
        node = node->next;
    }
    g_all_clear_cmd();
}
