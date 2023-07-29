/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 15:24:25 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	ft_home(void)
{
	char	*get_h;
	char	*s;

	s = getcwd(NULL, 0);
	get_h = get_node_value(g_all.env, "HOME");
	if (!get_h)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_all.status_val = 1;
	}
	else if (chdir(get_h) != 0)
	{
		perror ("chdir");
		free(get_h);
		free(s);
		return ;
	}
	else
	{
		replace("PWD", "PWD=", g_all.env, get_h);
		replace("OLDPWD", "OLDPWD=", g_all.env, s);
		free(get_h);
		free(s);
	}
}

void	ft_cd(char **argv, t_env *env)
{
	char	*path;
	char	*n_path;

	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
		ft_home();
	else
	{
		path = getcwd(NULL, 0);
		if (chdir(argv[1]) != 0)
		{
			if (errno == ENOTDIR)
				pr_err_not_a_dir(argv[1]);
			else
				pr_err_no_file(argv[1]);
			free(path);
			return ;
		}
		n_path = getcwd(NULL, 0);
		replace ("PWD", "PWD=", g_all.env, n_path);
		replace ("OLDPWD", "OLDPWD=", g_all.env, path);
		free(n_path);
		free(path);
	}
}
