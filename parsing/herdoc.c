/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:41:27 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 12:53:34 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

void	expand_herdoc(void)
{
	t_nodes	*node;
	t_nodes	*herdoc;

	node = g_all.head;
	while (node && node->next)
	{
		if (node && node->next && node->type == HERDOC
			&& node->next->type == SPACES)
		{
			herdoc = node;
			node = node->next->next;
			while (node && node->next && node->type != PIPES
				&& node->type != SPACES)
			{
				if (node && (node->type == D_Q || node->type == S_Q))
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

void	fd_dup(int *d, t_cmd *cmd, int *fd)
{
	*d = dup(0);
	dup2(g_all.dup_z, 0);
	g_all.k = 1;
	cmd->in = fd[1];
}

void	herdoc(t_nodes	*node, t_cmd *cmd, char *del, t_env *env)
{
	char	*l;
	int		d;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	fd_dup(&d, cmd, pipefd);
	while (1)
	{
		l = readline(">");
		if (!ft_strcmp(l, del) || !l)
		{
			free(l);
			break ;
		}
		wr_expand(l, node, env, pipefd[1]);
		free(l);
	}
	g_all.k = 0;
	close(pipefd[1]);
	dup2(d, 0);
}
