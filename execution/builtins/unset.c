/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/22 11:08:20 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_unset(int argc, char **argv)
{
    extern char **environ;
    char **env_ = environ;
    char **next = NULL;
    char *curr = NULL;
    int i = 1;

    while (i < argc)
    {
        env_ = environ;
        while (*env_ != NULL)
        {
            curr = *env_;
            if (ft_strncmp(curr, argv[i], ft_strlen(argv[i])) == 0
            && curr[ft_strlen(argv[i])] == '=')
            {
                next = env_;
                while (*next != NULL)
                {
                    *next = *(next + 1);
                    next++;
                }
                break;
            }
            env_++;
        }
        i++;
    }
}
