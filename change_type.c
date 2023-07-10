/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:35:10 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/10 19:45:30 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// focntion pour voir list create (nodes)
void    voir_nodes()
{
    t_nodes *head;

    head = g_all.head;
    while (head != NULL)
	{
		printf("\t\t----------\n");
		printf("type : [%d]\n", head->type);
		printf("valeur : [%s]\n", head->valeur);
		printf("quote : [%d]\n", head->quotes);
		printf("\t\t----------\n");
		head = head->next;
	}
    
}

void	check_nodes()
{
	t_nodes *head;

	head = g_all.head;
	while (head != NULL)
	{
		if (head->next && !ft_strcmp(head->valeur, "\""))
		{
			head = head->next;
			while (head->next && ft_strcmp(head->valeur, "\""))
			{
				head->quotes = 2;
				head = head->next;
			}			
		}
		if (head->next && !ft_strcmp(head->valeur, "'"))
		{
			head = head->next;
			while (head->next && ft_strcmp(head->valeur, "'"))
			{
				head->quotes = 1;
				head = head->next;
			}			
		}
		// if (head->next)
		head = head->next;
	}
}

void	change_type()
{
	t_nodes *head;

	head = g_all.head;
	while (head != NULL)
	{	
		if (head->next && head->quotes != 0 && (!ft_strcmp(head->valeur, "|") 
			|| !ft_strcmp(head->valeur, "<<") || !ft_strcmp(head->valeur, "<<") 
			|| !ft_strcmp(head->valeur, ">") || !ft_strcmp(head->valeur, ">>")))
				head->type = STRING;
		if (head->next && (!ft_strcmp(head->valeur, "<") && head->quotes == 0))
		{
			if (head->next->type == SPACES && head->next->next)
				head->next->next->type = IN_FILE;
			else
				head->next->type = IN_FILE;
		}
		if (head->next && (!ft_strcmp(head->valeur, ">") && head->quotes == 0))
		{	
			if (head->next->type == SPACES && head->next->next)
				head->next->next->type = OUT_FILE;
			else
				head->next->type = OUT_FILE;
		}
		// if (head->next && (ft_strcmp(head->valeur, "<>| $") && ft_strcmp(head->valeur, "\'") &&  ft_strcmp(head->valeur, "\"") ))
		// {
		// 	printf("avant (change) %d\n", head->type);
		// 	if (head->quotes != 0)
		// 	{
		// 		head->type = CMD;
		// 		printf("apres type (cmd) %d\n", head->type);
		// 	}
		// }
		head = head->next;
	}
}
