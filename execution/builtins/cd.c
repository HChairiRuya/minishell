/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 20:44:14 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	ft_dash(void)
{
	char	*get_old;

	get_old = getenv("OLDPWD");
	replace(g_all.env, get_old);
	if (get_old == NULL)
	{
		printf ("Previous directory not set.\n");
		return ;
	}
	if (chdir(get_old) != 0)
	{
		perror("chdir");
		return ;
	}
	printf("%s\n", get_old);
}

void	ft_previous(void)
{
	char	*pre;

	pre = "..";
	replace (g_all.env, pre);
	if (chdir(pre) != 0)
	{
		perror("chdir");
		return ;
	}
}

void	ft_home(void)
{
	char	*get_h;

	get_h = getenv("HOME");
	replace(g_all.env, get_h);
	if (chdir(get_h) != 0)
	{
		perror ("chdir");
		return ;
	}
}

char	*joiin_(char *path, char *h)
{
	char	*first;
	char	*sec;

	first = ft_strjoin(path, "/", 0);
	sec = ft_strjoin(first, h, 1);
	return (sec);
}

void	ft_cd(char **argv, t_env *env)
{
	char	*path;
	char	*n_path;

	path = getenv("OLDPWD");
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
		ft_home();
	else if (ft_strcmp(argv[1], "-") == 0)
		ft_dash();
	else if (ft_strcmp(argv[1], "~-") == 0)
		ft_previous();
	else
	{
		n_path = joiin_(path, argv[1]);
		replace(g_all.env, n_path);
		if (chdir(argv[1]) != 0)
		{
			if (errno == ENOTDIR)
				pr_err_not_a_dir(argv[1]);
			else
				pr_err_no_file(argv[1]);
			free(n_path);
			return ;
		}
		free(n_path);
	}
}
