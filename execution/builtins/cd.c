/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 09:17:37 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"
void ft_dash()
{
    char *get_old;

    get_old = getenv("OLDPWD");
    if (get_old == NULL)
    {
        printf("Previous directory not set.\n");
        return;
    }
    if (chdir(get_old) != 0)
    {
        perror("chdir");
        return ;
    }
    printf("%s\n", get_old);
}

void ft_previous()
{
    char *pre = "..";
    if (chdir(pre) != 0)
    {
        perror("chdir");
        return;
    }
}

void ft_home()
{
    char *get_h;

    get_h = getenv("HOME");
    if (chdir(get_h) != 0)
    {
        perror ("chdipr");
        return ;
    }  
}

void ft_cd(char **argv)
{
    if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
        ft_home();
    else if (ft_strcmp(argv[1], "-") == 0)
        ft_dash();
    else if (ft_strcmp(argv[1], "~-") == 0)
        ft_previous();
    else
    {
        if (chdir(argv[1]) != 0)
        {
            perror("chdir");
            return ;
        }
    }
}
