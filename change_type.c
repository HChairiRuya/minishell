/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:35:10 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/15 22:45:27 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	voir_nodes(void)
{
	t_nodes	*head;

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

void	check_nodes(void)
{
	t_nodes	*head;

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
		head = head->next;
	}
}

void	type_red(t_nodes *head)
{
	if (head->next && ((!ft_strcmp(head->valeur, "<")
				|| !ft_strcmp(head->valeur, "<<")) && head->quotes == 0))
	{
		if (head->next->type == SPACES && head->next->next)
			head->next->next->type = IN_FILE;
		else if (head->next->type == SPACES && !head->next->next)
			head->next->type = S_ERR;
		else
			head->next->type = IN_FILE;
	}
	if (head->next && ((!ft_strcmp(head->valeur, ">")
				|| !ft_strcmp(head->valeur, ">>")) && head->quotes == 0))
	{	
		if (head->next->type == SPACES && head->next->next)
			head->next->next->type = OUT_FILE;
		else if (head->next->type == SPACES && !head->next->next)
			head->next->type = S_ERR;
		else
			head->next->type = OUT_FILE;
	}
}

void	change_type(void)
{
	t_nodes	*head;

	head = g_all.head;
	while (head != NULL)
	{	
		if (head->next && head->quotes != 0 && (!ft_strcmp(head->valeur, "|")
				|| !ft_strcmp(head->valeur, "<<")
				|| !ft_strcmp(head->valeur, "<")
				|| !ft_strcmp(head->valeur, ">")
				|| !ft_strcmp(head->valeur, ">>")))
				{
						// while (1);
				head->type = STRING;
				}
	
		type_red(head);
		head = head->next;
	}
}
