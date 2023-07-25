/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 20:43:21 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void replace(t_env *env, char *value)
{
    char **key_value;

    while (env)
    {
        key_value = ft_split(env->s, '=');
        if (!ft_strncmp(key_value[0], "PWD", ft_strlen(env->s)))
        {
                   printf ("KEY VAL: %s\n", key_value[1]);
                printf ("VALUE: %s\n", value);
            if (ft_strncmp(key_value[1], value, ft_strlen(env->s)))
            {
                free(env->s);
                env->s = "";
                env->s = ft_strjoin(env->s, "PWD=", 0);
                env->s = ft_strjoin(env->s, value, 0);
                printf ("ENV: %s\n", env->s);
                break ;
            }
        }
        env = env->next;
    }
}

void ft_dash()
{
    char *get_old;

    get_old = getenv("OLDPWD");
    replace(g_all.env, get_old);
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
    char *pre;

    pre = "..";
    replace (g_all.env, pre);
    printf ("cd 1: %s\n", g_all.env->s);
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
    replace(g_all.env, get_h);
    printf ("cd 2: %s\n", get_h);
    if (chdir(get_h) != 0)
    {
        perror ("chdipr");
        return ;
    }  
}

void ft_cd(char **argv, t_env *env)
{
    char *path;

    path = getenv("PWD");
    if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
        ft_home();
    else if (ft_strcmp(argv[1], "-") == 0)
        ft_dash();
    else if (ft_strcmp(argv[1], "~-") == 0)
        ft_previous();
    else
    {
        printf ("cd 3: %s\n", path);
        if (chdir(argv[1]) != 0)
        {
            perror("chdir");
            return ;
        }
    }
}
