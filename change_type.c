/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:35:10 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/09 19:41:24 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  Voici un exemple de code en C qui divise la commande shell sans utiliser la fonction strtok 


// focntion pour voir list create (nodes)
void    voir_nodes()
{
    t_nodes *head;

    head = g_all.head;
    while (head != NULL)
	{
		printf("\t\t------\n");
		printf("type : [%d]\n", head->type);
		printf("valeur : [%s]\n", head->valeur);
		printf("quote : [%d]\n", head->quotes);
		printf("\t\t------\n");
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
		if (head->next && (!ft_strcmp(head->valeur, "|") || !ft_strcmp(head->valeur, "<<") || !ft_strcmp(head->valeur, "<<") 
			|| !ft_strcmp(head->valeur, ">") || !ft_strcmp(head->valeur, ">>")))
		{
			// printf("avant change %d\n", head->type);
			if (head->quotes != 0)
			{
				head->type = STRING;
				// printf("apres change %d\n", head->type);
			}
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
