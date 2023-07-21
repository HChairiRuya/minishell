/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:08:46 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/21 10:34:01 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void free_pipes(t_path *path)
{
	int i;

	i = 0;
	if (path->pipes_fd)
	{
		while (i < path->n_pipes)
		{
			if (path->pipes_fd[i])
				free(path->pipes_fd[i]);
		}
		i++;
		free(path->pipes_fd);
		path->pipes_fd = NULL;
	}
}

int cr_pipes(t_path *path)
{
    int i;

    i = 0;
    path->pipes_fd = malloc(path->n_pipes * sizeof(int *) * 2);
    if (path->pipes_fd == NULL)
        return (1);
    while (i < path->n_pipes)
    {
        if (pipe(path->pipes_fd[i]) == -1)
        {
            perror("pipe");
            free_pipes(path);
            return (1);
        }
        i++;
    }
    return (0);
}

void close_pipes(t_path *path)
{
	int i;
	
	i = 0;
	while (i < path->n_pipes)
	{
		close(path->pipes_fd[i][0]);
		close(path->pipes_fd[i][1]);
		i++;
	}
}

void dupps(int fd, t_path *path, t_cmd *cmd)
{
	if (fd == 0 && fd != path->n_args - 1)
	{
		if (dup2(path->pipes_fd[fd][1], STDOUT_FILENO) == -1)
		{
			perror("dup2-");
			return;
		}
		close(path->pipes_fd[fd][0]);
		close(path->pipes_fd[fd][1]);
	}
	if (fd > 0 && fd < path->n_args - 1)
	{
		if (dup2(path->pipes_fd[fd - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2--");
			return;
		}
		close(path->pipes_fd[fd - 1][0]);
		close(path->pipes_fd[fd - 1][1]);
		if (dup2(path->pipes_fd[fd][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return;
		}
		close(path->pipes_fd[fd][0]);
		close(path->pipes_fd[fd][1]);
	}
	if (fd == path->n_args - 1 && fd != 0)
	{
		if (dup2(path->pipes_fd[fd - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return;
		}
		close(path->pipes_fd[fd - 1][0]);
		close(path->pipes_fd[fd - 1][1]);
	}
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

int forking_for_pipe(t_path *pt, t_cmd *cmd, int i)
{
	g_all.child[i] = fork();
	if (g_all.child[i] == 0)
	{
		dupps(i, pt, cmd);
		close_pipes(pt);
		// printf ("%s\n", cmd->data[0]);
		execve(pt->found, cmd->data, NULL);
		errno = ENOENT;
   		perror("command not found");
		exit (0);
	}
	return (0);
}

int start(t_path *pt)
{
	t_cmd *cmd;
	int i;
	char *path;

	i = 0;
	cmd = g_all.cmd;
	path = getenv("PATH");
	pt->splitted = ft_split(path, ':');
	if (cr_pipes(pt) == 1)
	{
		perror("cr_pipes");
		return (1);
	}
	while (cmd)
	{
		iterate(pt, cmd->data[0]);
		forking_for_pipe(pt, cmd, i);
		if (g_all.child[i] == 0)
			break ;
		i++;
		cmd = cmd->next;
	}
	i = -1;
	close_pipes(pt);
	while (++i < pt->n_args)
		waitpid(g_all.child[i], NULL, 0);
	free(pt);
	return (0);
}

int pipin(int argc)
{
	t_path *path;

	path = NULL;
	path = malloc(sizeof(t_path));
	if (!path)
		return (0);
	path->n_args = argc;
	path->n_pipes = path->n_args - 1;
	g_all.child = malloc(sizeof(int) * path->n_pipes);
	start(path);
	return (0);
}
