/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/20 11:45:13 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_cd(char **argv)
{
    char *get_h;

    if (argv[1] == NULL)
    {
        get_h = getenv("HOME");
        if (chdir(get_h) != 0)
        {
            perror ("chdipr");
            return ;
        }  
    }
    else if (chdir(argv[1]) != 0)
	{
        perror("chdir");
        return ;
    }
}
