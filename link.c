/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:35:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/10 22:52:25 by hchairi          ###   ########.fr       */
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
    // printf("\tfirst val : %s\n", first->valeur);
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
        if (node && node->type < 7)
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
        i = -1;
        count = ft_count(node);
        printf("couuuunt %d\n", count);
        data = malloc(sizeof(char **) * (count + 1));
        if (!data)
            return ;
        while (node && node->type != PIPES)
        {
            if (node && node->type < 7)
                data[++i] = ft_strdup(node->valeur);
            printf("iii%d\n", i);
            node = node->next;
        }
        printf("waach\n");
        lstaddback_cmd(lstnew_cmd(data));
        printf("helllloooo\n");
        if (node && node->next)
            node = node->next;
        
    }
}