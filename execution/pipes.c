/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:08:46 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 14:57:50 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void dupps(int fd, t_path *path, t_cmd *cmd)
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

int forking_for_pipe(t_path *pt, t_cmd *cmd, int i)
{
	g_all.child[i] = fork();
	if (g_all.child[i] == 0)
	{
		if (!cmd->data[0])
			exit (0) ;
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

int start(t_path *pt)
{
	t_cmd *cmd;
	int i;
	char *path;

	i = 0;
	cmd = g_all.cmd;
	path = find_path(g_all.env);
	pt->splitted = ft_split(path, ':');
	if (hi(cmd, pt) == 0)
		return (0);
	else
	{
		while (cmd)
		{
			iterate(pt, cmd->data[0]);
			forking_for_pipe(pt, cmd, i);
			free(pt->found);
			if (g_all.child[i] == 0)
				break ;
			i++;
			cmd = cmd->next;
		}
		end(pt);
	}
	return (0);
}

int execution(int argc)
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
	return (0);
}
