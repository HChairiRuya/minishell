/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:08:46 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 12:34:11 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void	dupps(int fd, t_path *path, t_cmd *cmd)
{
	if (fd == 0 && fd != path->n_args - 1)
		dup_first(path, fd);
	if (fd > 0 && fd < path->n_args - 1)
		dup_middle(path, fd);
	if (fd == path->n_args - 1 && fd != 0)
		dup_end(path, fd);
	if (cmd->in != 0)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
}

void	forking_for_pipe(t_path *pt, t_cmd *cmd, int i)
{
	g_all.child[i] = fork();
	if (g_all.child[i] == 0)
	{
		if (!cmd->data[0])
			exit (0);
		if (if_bt_found(cmd->data) == 1)
		{
			dupps(i, pt, cmd);
			close_pipes(pt);
			builtins(count_ac(), cmd->data);
			exit (0);
		}
		else
		{
			dupps(i, pt, cmd);
			close_pipes(pt);
			if (execve(pt->found, cmd->data, g_all.envr) == -1)
				print_err(cmd, pt->found);
		}
	}
}

int	start_exec(t_path *pt, t_cmd *cmd, char *path)
{
	int	i;

	i = 0;
	cmd = g_all.cmd;
	path = find_path(g_all.env);
	pt->splitted = ft_split(path, ':');
	if (cr_pipes(pt) == 1)
	{
		perror("cr_pipes");
		ft_free_split(pt->splitted);
		free(path);
		return (1);
	}
	while (cmd)
	{
		iterate(pt, cmd->data[0]);
		forking_for_pipe(pt, cmd, i);
		if (g_all.child[i] == 0)
			break ;
		free(pt->found);
		i++;
		cmd = cmd->next;
	}
	return (0);
}

int	start(t_path *pt)
{
	t_cmd	*cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = g_all.cmd;
	path = find_path(g_all.env);
	pt->splitted = ft_split(path, ':');
	if (if_bt_found(cmd->data) && count_nd() == 1)
	{
		dupps(0, pt, cmd);
		pt->pipes_fd = NULL;
		builtins(count_ac(), cmd->data);
		close(0);
		close(1);
		dup2(g_all.dup_z, 0);
		dup2(g_all.dup_o, 1);
		free(path);
		return (0);
	}
	start_exec(pt, cmd, path);
	close_pipes(pt);
	wait_pid(pt);
	free(path);
	return (0);
}

int	execution(int argc)
{
	t_path	*path;

	path = NULL;
	path = malloc(sizeof(t_path));
	if (!path)
		return (0);
	path->n_args = argc;
	if (path->n_args)
	{
		path->n_pipes = path->n_args - 1;
		g_all.child = malloc(sizeof(pid_t) * path->n_pipes);
		if (!g_all.child)
		{
			free(path);
			return (0);
		}
		start(path);
		free(path->pipes_fd);
		ft_free_split(path->splitted);
		free(g_all.child);
	}
	free(path);
	return (0);
}
