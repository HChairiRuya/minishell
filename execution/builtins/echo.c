/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:03:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 13:26:44 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int ft_strcmp_ch(char c, char target)
{
    return c == target ? 0 : 1;
}

int ft_cmp(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

void ft_echo(int argc, char **argv)
{
    char *n;
    int no_nl;
	int i;

	i = 1;
	no_nl = 0;
    n = NULL;
    while (argv[i])
    {
        n = ft_strchr(argv[i], 'n');
        if (argc >= 2 && ft_strcmp_ch(argv[i][0], '-') == 0
        && argv[i][0] == '-' && argv[i][1] == 'n')
        {
            if (ft_cmp(n) == 1)
                break;
            else
            {
                no_nl = 1;
                argv++;
                argc--;
            }
            continue;
        }
        else
            break;
        i++;
        n = NULL;
    }
    argv++;
    i = 0;
    while (argv[i])
    {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    if (!no_nl)
        printf("\n");
}
