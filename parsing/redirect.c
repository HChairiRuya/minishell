/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:11:25 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/21 10:40:40 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	*get_next(t_nodes *node)
{
	while (node && (node->type == SPACES
			|| node->type == DOUBLES_QUOTES
			|| node->type == SINGLE_QUOTES))
		node = node->next;
	return (node);
}

void	wr_expand(char *l, t_nodes *node, t_env	*env, int fd)
{
	char	*to_expand;
	char	*exp;
	int		i;
	int		j;

	i = -1;
	while (l[++i])
	{
		if (l[i] == '$' && node->check == 0)
		{
			j = ++i;
			if (l[i] == '_' || ft_isalpha(l[i]))
			{
				while (l[++i] && (l[i] == '_' || ft_isalnum(l[i])))
					;
				to_expand = ft_substr(l, j, i - j);
				exp = get_node_value(env, to_expand);
				ft_putstr_fd(exp, fd);
			}
		}
		else
			write(fd, &l[i], 1);
	}
	write(fd, "\n", 1);
}

void	expand_herdoc(void)
{
	t_nodes	*node;
	t_nodes	*herdoc;

	node = g_all.head;
	while (node && node->next)
	{
		if (node && node->next && node->type == HERDOC && node->next->type == SPACES)
		{
			herdoc = node;
			node = node->next->next;
			while (node && node->next && node->type != PIPES && node->type != SPACES)
			{
				if (node && (node->type == DOUBLES_QUOTES || node->type == SINGLE_QUOTES))
				{
					herdoc->check = 1;
					return ;
				}
				node = node->next;
			}
		}
		if (node && node->next)
			node = node->next;
	}
}

void	herdoc(t_nodes	*node, t_cmd *cmd, char *del, t_env *env)
{
	char	*l;
	int		i;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	cmd->in = pipefd[0];
	while (1)
	{
		i = 0;
		l = readline(">");
		if (!ft_strcmp(l, del))
		{
			free(l);
			break ;
		}
		wr_expand(l, node, env, pipefd[1]);
		free(l);
	}
	close(pipefd[1]); // Close the read end of the pipe
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
