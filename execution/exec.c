/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:26:34 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/22 13:31:50 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int check_com(char *path)
{
	if (!access(path, R_OK))
	{
		if (!access(path, X_OK))
			return (1);
		else
			return (2);
	}
	return (0);
}

int iterate(t_path *path, char *args)
{
	char	**token;
	char	*full_path;
	char	*str;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	token = path->splitted;
	if (ft_strchr(args, '/') != NULL)
    {
        path->found = args;
        return (1);
    }
	while (token && token[i] != NULL)
	{
		full_path = get_full_path(token[i], args);
		if (check_com(full_path) == 1
			&& ft_strncmp(token[i], args, ft_strlen(token[i])))
		{
			path->found = full_path;
			flag = 1;
			break;
		}
		else
		{
			path->found = NULL;
			free(full_path);
		}
		i++;
	}
	return (flag);
}

int forking(const char *cmd, char **args)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("fork");
		return (2);
	}
	if (child == 0)
	{
		execve(cmd, args, NULL);
		perror("execve");
		return (1);
	}
	else
		waitpid(child, NULL, 0);
	return (0);
}

int executin(t_cmd *cmd, char **argv)
{
	t_path *pt;
	char *path;

	pt = NULL;
	pt = malloc(sizeof(t_path));
	if (pt == NULL)
		return (1);
	pt->found = NULL;
	path = getenv("PATH");
	pt->splitted = ft_split(path, ':');
	if (iterate(pt, cmd->data[0]) == 1)
	{
	   if (pt->found != NULL)
		   return (forking(pt->found, cmd->data));
	   else
		   return (1);
	}
	free(pt);
	return (0);
}
