/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:26:34 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/18 16:54:41 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int check_com(char *path, char *cmd)
{
	DIR *dir;

	dir = opendir(path);
	struct dirent *entry;

	if (dir == NULL)
	{
		perror("opendir");
		return (0);
	}

	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_strcmp(entry->d_name, cmd) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
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
		if (access(token[i], R_OK) == 0)
		{
			if (check_com(token[i], args) == 1)
			{
				full_path = get_full_path(token[i], args);
				path->found = full_path;
				flag = 1;
				break;
			}
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
