/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:07:44 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/27 12:22:02 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_node_value(t_env *head, char *var)
{
	t_env	*curr;

	if (!var)
		return (NULL);
	curr = head;
	if (!ft_strncmp(var, "$", 1))
		return (ft_strdup("1337"));
	if (!ft_strncmp(var, "?", 1))
		return (ft_itoa(g_all.status_val));
	while (curr != NULL)
	{
		if (ft_strncmp(curr->s, var, ft_strlen(var)) == 0
			&& curr->s[ft_strlen(var)] == '=')
			return (ft_substr(curr->s, ft_strlen(var)
					+ 1, ft_strlen(curr->s) - ft_strlen(var)));
		curr = curr->next;
	}
	return (NULL);
}

int	check_node(t_nodes *node)
{
	int	i;

	i = 0;
	if (node->valeur && (node->valeur[i] == '_' || ft_isalpha(node->valeur[i])))
		while (node->valeur
			&& (node->valeur[++i] == '_' || ft_isalnum(node->valeur[i])))
			;
	else
		i = 1;
	return (i);
}

t_nodes	*cas_expand(t_nodes *head, char *expand_val, t_nodes *save, int i)
{
	char	*s;

	if (head->type == DOLLAR && !head->next)
		return (head);
	if (head && head->next && head->type == DOLLAR && head->quotes == 0)
	{
		if (check_space(expand_val))
		{
			save_list(&save, expand_val);
			if (save && head->next->next)
				ft_lstlast(save)->next = head->next->next;
			delete_node_expanded(head, save);
			head = save;
		}
	}
	if (head && head->next && head->type == DOLLAR
		&& head->quotes != 1 && !char_special(head->next->valeur[0]))
	{
		s = ft_substr(head->next->valeur, i, ft_strlen(head->next->valeur));
		free(head->valeur);
		head->valeur = ft_strjoin(expand_val, s, 2);
		free_node_exp(head);
	}
	return (head);
}

char	*global_expand(t_env *env)
{
	t_nodes	*head;
	t_nodes	*save;
	char	*expand_val;
	char	*value;
	int		i;

	head = g_all.head;
	save = NULL;
	while (head != NULL && head->next != NULL)
	{
		i = check_node(head->next);
		value = ft_substr(head->next->valeur, 0, i);
		expand_val = get_node_value(env, value);
		head = cas_expand(head, expand_val, save, i);
		free(expand_val);
		free(value);
		if (head)
			head = head->next;
	}
	rm_quotes();
	link_strings();
	link_tous();
	return (NULL);
}
