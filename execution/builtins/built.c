/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:12:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 16:15:06 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	pr_error_nf(char *args)
{
	write (2, "env: ", ft_strlen("env: "));
	write (2, args, ft_strlen(args));
	write (2, ": ", 2);
	write (2, "No such file or directory\n",
		ft_strlen("No such file or directory\n"));
	g_all.status_val = 127;
}

void	builtins(int argc, char **argv)
{
	g_all.status_val = 0;
	if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
	{
		if (argc == 1)
			pr_env(g_all.env);
		else
			pr_error_nf(argv[1]);
	}
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv, g_all.env);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argc, argv, g_all.env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argv, &g_all.env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		ft_exit_e(argc, argv);
}

int	if_bt_found(char **argv)
{
	if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "echo")
		|| !ft_strcmp(argv[0], "exit") || !ft_strcmp(argv[0], "env")
		|| !ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "export")
		|| !ft_strcmp(argv[0], "unset"))
		return (1);
	return (0);
}
