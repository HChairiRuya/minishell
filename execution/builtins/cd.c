/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/17 15:45:14 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_cd(char **argv) 
{
    if (chdir(argv[2]) != 0)
	{
        perror("chdir");
        return;
    }
    printf("yeaa\n");
    if (argv[3] != NULL)
	{
        char *arg[] = {argv[3], NULL};
        execve(arg[0], arg, NULL);
        perror("execvp");
        return;
    }
	ft_pwd();
}