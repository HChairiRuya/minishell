/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:45:15 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/22 18:30:33 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_exit_e(int argc, char **argv)
{
	char *arg;
	int i;

	arg = argv[1];
	i = 0;
    if (argc == 1)
	{
        printf("exit\n");
        exit(0);
    }
	else if (argc == 2)
	{
        while (arg[i])
		{
            if (!ft_isdigit(arg[i]))
			{
                printf("numeric argument required\n");
                exit(1);
            }
            i++;
        }
        printf("exit\n");
        exit(ft_atoi(arg));
    }
	else
	{
        printf("too many arguments\n");
        return ;
    }
}

