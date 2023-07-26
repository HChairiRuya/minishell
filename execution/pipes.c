/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:08:46 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/26 19:18:11 by fbelahse         ###   ########.fr       */
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
			i++;
		}
		free(path->pipes_fd);
		path->pipes_fd = NULL;
	}
}

int cr_pipes(t_path *path)
{
    int i;

    i = 0;
    path->pipes_fd = malloc(path->n_pipes * sizeof(int *));
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
	t_cmd *tmp;
	
	i = 0;
	tmp = g_all.cmd;
	while (i < path->n_pipes)
	{
		close(path->pipes_fd[i][0]);
		close(path->pipes_fd[i][1]);
		i++;
	}
	while (tmp)
	{
		if (tmp->in != 0)
			close(tmp->in);
		if (tmp->out != 1)
			close(tmp->out);
		tmp = tmp->next;
	}
}

void dupps(int fd, t_path *path, t_cmd *cmd)
{
	if (fd == 0 && fd != path->n_args - 1)
	{
		if (dup2(path->pipes_fd[fd][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return;
		}
		close(path->pipes_fd[fd][0]);
		close(path->pipes_fd[fd][1]);
	}
	if (fd > 0 && fd < path->n_args - 1)
	{
		if (dup2(path->pipes_fd[fd - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
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

void print_err(t_cmd *cmd, char *args)
{
	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	if (check_com(args) == 2)
	{
		perror(cmd->data[0]);
		exit (126);
	}
	else
	{
		write (2, cmd->data[0], ft_strlen(cmd->data[0]));
		write (2, ": ", 2);
		write (2, "command not found\n", ft_strlen("command not found\n"));
		exit (127);
	}
}

int forking_for_pipe(t_path *pt, t_cmd *cmd, int i)
{
	if (if_bt_found(cmd->data) && count_nd() == 1)
	{
        builtins(count_ac(), cmd->data);
		return (0);
	}
	g_all.child[i] = fork();
	if (g_all.child[i] == 0)
	{
		if (if_bt_found(cmd->data) == 1)
		{
			dupps(i, pt, cmd);
			close_pipes(pt);
			builtins(count_ac(), g_all.cmd->data);
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
    return (0);
}

void ft_free_split(char **split)
{
	if (split)
	{
		size_t i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

char *find_path(t_env *env)
{
    char **key_value;
	char *path;

    while (env)
    {
        key_value = ft_split(env->s, '=');
        if (!ft_strncmp(key_value[0], "PATH", ft_strlen(env->s)))
		{
            path = key_value[1];
			break;
		}
        env = env->next;
    }
	return (path);
}

int start(t_path *pt)
{
	t_cmd *cmd;
	int i;
	int status;
	int ex_code;
	char *path;

	i = 0;
	status = 0;
	ex_code = 0;
	cmd = NULL;
	cmd = g_all.cmd;
	path = find_path(g_all.env);
	pt->splitted = ft_split(path, ':');
	if (cr_pipes(pt) == 1)
	{
		perror("cr_pipes");
		// ft_free_split(pt->splitted); //free test split
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
		waitpid(g_all.child[i], &status, 0);
	g_all.status_val = 0;
	if (WIFEXITED(status))
	{
		ex_code = WEXITSTATUS(status);
		if (ex_code != 0)
			g_all.status_val = ex_code;
	}
	free(pt);
	return (g_all.status_val);
}

int pipin(int argc)
{
	t_path *path;
	int ex_st;

	path = NULL;
	ex_st = 0;
	path = malloc(sizeof(t_path));
	if (!path)
		return (0);
	path->n_args = argc;
	if (path->n_args)
	{
		path->n_pipes = path->n_args - 1;
		g_all.child = malloc(sizeof(pid_t) * path->n_pipes);
		if (!g_all.child)// free test
		{
			free(path); // Free path in case of allocation failure
			return (0);
		}
	start(path);
	free(g_all.child);
	// free(g_all.child); // Free the memory allocated for g_all.child  // free test
	// free(path); // Free the memory allocated for path // free test
	}
	
	return (g_all.status_val);
}
