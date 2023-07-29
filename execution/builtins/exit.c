/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:45:15 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 09:51:41 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	pr_erro_o(void)
{
	write (2, "minishell: ", ft_strlen("minishell: "));
	write (2, "exit: ", ft_strlen("exit: "));
	write (2, "too many arguments\n", ft_strlen("too many arguments\n"));
}

void	pr_erro_t(char *argv)
{
	write (2, "minishell: ", ft_strlen("minishell: "));
	write (2, "exit: ", ft_strlen("exit: "));
	write (2, argv, ft_strlen(argv));
	write (2, ": ", 2);
	write (2, "numeric argument required\n",
		ft_strlen("numeric argument required\n"));
}

void	ft_exit(int var)
{
	free(g_all.line);
	g_all_clear();
	lstclear_env();
	g_all_clear_cmd();
	exit(var);
}

void	ft_exit_e(int argc, char **argv)
{
	int	i;
	int	var;

	i = 0;
	var = g_all.status_val;
	if (argc == 1 || (argc == 2 && ft_isdigit(argv[1][0])))
		printf("exit\n");
	else if (!ft_isdigit(argv[1][0]))
	{
		printf ("exit\n");
		pr_erro_t(argv[1]);
		var = 255;
	}
	else if (argc > 2 && ft_isdigit(argv[1][0]))
	{
		printf("exit\n");
		pr_erro_o();
		return ;
	}
	ft_exit(var);
}
