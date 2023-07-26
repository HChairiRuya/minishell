/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:04:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 16:48:26 by fbelahse         ###   ########.fr       */
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
    if (chdir(get_h) != 0)
    {
        perror ("chdipr");
        return ;
    }  
}

char* joiin_(char *path, char *h)
{
    char *first;
    char *sec;

    first = ft_strjoin(path, "/", 0);
    sec = ft_strjoin(first, h, 0);
    return (sec);
}

void pr_err(char *args)
{
    write (0, "minishell: ", ft_strlen("minishell: "));
    write (0, "cd: ", ft_strlen("cd: "));
    write (0, args, ft_strlen(args));
    write (0, ": ", 2);
    write (0, "No such file or directory\n", ft_strlen("No such file or directory\n"));
}

void pr_errorno(char *args)
{
    write (0, "minishell: ", ft_strlen("minishell: "));
    write (0, "cd: ", ft_strlen("cd: "));
    write (0, args, ft_strlen(args));
    write (0, ": ", 2);
    write (0, "Not a directory\n", ft_strlen("Not a directory\n"));
}

void ft_cd(char **argv, t_env *env)
{
    char *path;
    char *n_path;

    path = getenv("OLDPWD");
    if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
        ft_home();
    else if (ft_strcmp(argv[1], "-") == 0)
        ft_dash();
    else if (ft_strcmp(argv[1], "~-") == 0)
        ft_previous();
    else
    {
        n_path = joiin_(path, argv[1]);
        replace(g_all.env, n_path);
        if (chdir(argv[1]) != 0)
        {
            if (errno == ENOTDIR)
                pr_errorno(argv[1]);
            else 
                pr_err(argv[1]);
            return ;
        }
    }
}
