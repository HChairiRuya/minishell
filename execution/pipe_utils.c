/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:35:20 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/27 16:38:49 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void dup_first(t_path *path, int fd)
{
	if (dup2(path->pipes_fd[fd][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return;
	}
	close(path->pipes_fd[fd][0]);
	close(path->pipes_fd[fd][1]);
}

void dup_middle(t_path *path, int fd)
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

void dup_end(t_path *path, int fd)
{
	if (dup2(path->pipes_fd[fd - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return;
		}
		close(path->pipes_fd[fd - 1][0]);
		close(path->pipes_fd[fd - 1][1]);
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

char *find_path(t_env *env)
{
    char **key_value;
	char *path;
	int i;

	i = 0;
    while (env)
    {
        key_value = ft_split(env->s, '=');
        if (!ft_strncmp(key_value[0], "PATH", ft_strlen(env->s)))
		{
            path = key_value[1];
			i = 0;
			while (key_value[i])
			{
				if (i != 1)
					free(key_value[i]);
				i++;
			}
			free(key_value);
			break;
		}
		i = 0;
		while (key_value[i])
		{
			free(key_value[i]);
			i++;
		}
		free(key_value);
        env = env->next;
    }
	return (path);
}