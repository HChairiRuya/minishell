/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:23:54 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 15:06:02 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	replace(t_env *env, char *value)
{
	char	**key_value;

    while (env)
    {
        key_value = ft_split(env->s, '=');
        if (!ft_strncmp(key_value[0], "PWD", ft_strlen(env->s)))
        {
            if (ft_strncmp(key_value[1], value, ft_strlen(env->s)))
            {
                free(env->s);
                env->s = "";
                env->s = ft_strjoin(env->s, "PWD=", 0);
                env->s = ft_strjoin(env->s, value, 0);
                break ;
            }
        }
        env = env->next;
    }
}

void	pr_err_no_file(char *args)
{
    write (2, "minishell: ", ft_strlen("minishell: "));
    write (2, "cd: ", ft_strlen("cd: "));
    write (2, args, ft_strlen(args));
    write (2, ": ", 2);
    write (2, "No such file or directory\n", ft_strlen("No such file or directory\n"));
    g_all.status_val = 1;
}

void	pr_err_not_a_dir(char *args)
{
    write (2, "minishell: ", ft_strlen("minishell: "));
    write (2, "cd: ", ft_strlen("cd: "));
    write (2, args, ft_strlen(args));
    write (2, ": ", 2);
    write (2, "Not a directory\n", ft_strlen("Not a directory\n"));
    g_all.status_val = 1;
}
