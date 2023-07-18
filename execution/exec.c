/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:26:34 by fbelahse          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/18 21:49:00 by fbelahse         ###   ########.fr       */
=======
/*   Updated: 2023/07/18 16:54:41 by hchairi          ###   ########.fr       */
>>>>>>> 7ae2bcd6248835a8a020d12f7f2ac4f8e0b1618d
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int check_com(char *path)
{
	if (!access(path, F_OK))
	{
		if (!access(path, X_OK))
			return (1);
	}
	return (0);
}

int iterate(t_path *path, char *args)
{
	char	**token;
	char	*full_path;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	token = path->splitted;
	while (token[i] != NULL)
	{
		full_path = get_full_path(token[i], args);
		if (check_com(full_path) == 1)
		{
			path->found = full_path;
			flag = 1;
			break;
		}
		else
			path->found = NULL;
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
