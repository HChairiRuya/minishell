/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:12:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/22 12:28:14 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void builtins(int argc, char **argv)
{
	extern char **environ; 
	if (ft_strcmp(argv[0], "pwd") == 0 && argc == 1)
		ft_pwd();
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0 && argc == 1)
		ft_env();
	else if (ft_strcmp(argv[0], "cd") == 0)
		ft_cd(argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		ft_export(argc, argv);
	else if(ft_strcmp(argv[0], "unset") == 0)
		ft_unset(argc, argv);
	else if (ft_strcmp(argv[0], "exit") == 0 && argc == 1)
		exit(0);

}

int if_bt_found(char **argv)
{
	if (!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "echo")
		|| !ft_strcmp(argv[0], "exit") || !ft_strcmp(argv[0], "env")
		|| !ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "export")
		|| !ft_strcmp(argv[0], "unset"))
		return (1);
	return (0);
}
