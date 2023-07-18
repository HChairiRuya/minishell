/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:03:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/18 23:40:00 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_echo(int argc, char **argv)
{
	int no_nl;

	no_nl = 0;
    if (argc >= 2 && ft_strncmp(argv[0], "echo", ft_strlen("echo")) == 0)
    {
		if (argc >= 3 && ft_strncmp(argv[1], "-n", ft_strlen("-n")) == 0 
			&& ft_strncmp(argv[1], "-n", ft_strlen("-n")) == 0)
		{
			no_nl = 1;
			argv += 3;
		}
		else
			argv += 2;
        while (*argv)
        {
            printf("%s", *argv);
            if (*(argv + 1))
                printf(" ");
            argv++;
        }
		if (!no_nl)
        	printf("\n");
    }
}