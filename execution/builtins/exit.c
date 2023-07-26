/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:45:15 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 12:40:09 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void pr_erro_o()
{
    write (0, "minishell: ", ft_strlen("minishell: "));
    write (0, "exit: ", ft_strlen("exit: "));
    write (0, "too many arguments\n", ft_strlen("too many arguments\n"));
}

void pr_erro_t(char *argv)
{
    write (0, "minishell: ", ft_strlen("minishell: "));
    write (0, "exit: ", ft_strlen("exit: "));
    write (0, argv, ft_strlen(argv));
    write (0, ": ", 2);
    write (0, "numeric argument required\n", ft_strlen("numeric argument required\n"));
}

void ft_exit_e(int argc, char **argv)
{
	int i;

	i = 0;
    if (argc == 1 || (argc == 2 && ft_isdigit(argv[1][0])))
	{
        printf("exit\n");
        exit(1);
    }
	else if (!ft_isdigit(argv[1][0]))
	{
        printf ("exit\n");
        pr_erro_t(argv[1]);
        exit(1);
    }
	else if (argc > 2 && ft_isdigit(argv[1][0]))
	{
        printf("exit\n");
        pr_erro_o();
        return ;
    }
}
