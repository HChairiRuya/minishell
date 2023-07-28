/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:11:25 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/27 15:15:45 by hchairi          ###   ########.fr       */
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

void	fd_error(char *args, t_cmd *cmd)
{
	g_all.fde = 1;
	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	perror(args);
	if (cmd->out != 1)
		close(cmd->out);
	if (cmd->in != 0)
		close(cmd->in);
}

int	redirect_cases(t_nodes *node, t_cmd *cmd, t_env *env)
{
	if (node->type == APPEND || node->type == RED_OUT)
		if (cmd->out != 1)
			close(cmd->out);
	if (node->type == RED_IN || node->type == HERDOC)
		if (cmd->in != 0)
			close(cmd->in);
	if (node->type == RED_OUT)
		cmd->out = open(get_next(node->next)->valeur,
				O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (node->type == APPEND)
		cmd->out = open(get_next(node->next)->valeur,
				O_RDWR | O_CREAT | O_APPEND, 0664);
	if (node->type == RED_IN)
		cmd->in = open(get_next(node->next)->valeur, O_RDWR, 0664);
	if (node->type == HERDOC)
		herdoc(node, cmd, get_next(node->next)->valeur, env);
	if (cmd->out == -1 || cmd->in == -1)
	{
		fd_error(get_next(node->next)->valeur, cmd);
		return (1);
	}
	return (0);
}

void	redirect(t_cmd *cmd, t_env *env)
{
	t_nodes	*node;

	node = g_all.head;
	while (node)
	{
		if (node->type >= 5 && node->type <= 8)
		{
			if (redirect_cases(node, cmd, env))
				break ;
		}
		else if (node->type == PIPES && cmd->next)
			cmd = cmd->next;
		node = node->next;
	}
}
