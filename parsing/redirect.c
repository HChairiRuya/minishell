/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:11:25 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 15:56:29 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	*get_next(t_nodes *node)
{
	while (node && (node->type == SPACES
		|| node->type == D_Q || node->type == S_Q))
		node = node->next;
	return (node);
}

void	redirect_cases(t_nodes *node, t_cmd *cmd, t_env *env)
{
	(void)env;
	if (node->type == RED_OUT)
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = open(get_next(node->next)->valeur, O_RDWR | O_CREAT, 0664);
	}
	if (node->type == APPEND)
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = open(get_next(node->next)->valeur,
				O_RDWR | O_CREAT | O_APPEND, 0664);
	}
	if (node->type == RED_IN)
	{
		if (cmd->in != 0)
			close(cmd->in);
		cmd->in = open(get_next(node->next)->valeur, O_RDWR, 0664);
	}
	if (node->type == HERDOC)
	{
		if (cmd->in != 0)
			close(cmd->in);
		herdoc(node, cmd, get_next(node->next)->valeur, env);
	}
}

void	redirect(t_cmd *cmd, t_env *env)
{
	t_nodes	*node;

	node = g_all.head;
	while (node)
	{
		if (node->type >= 5 && node->type <= 8)
			redirect_cases(node, cmd, env);
		else if (node->type == PIPES && cmd->next)
			cmd = cmd->next;
		node = node->next;
	}
}
