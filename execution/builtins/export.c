/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:49:21 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/23 09:57:17 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void add_n_env(char ***env, char *argv)
{
    int env_len;
    char **n_env;

    env_len = 0;
    while ((*env)[env_len] != NULL)
        env_len++;
    n_env = malloc((env_len + 2) * sizeof(char *));
    if (!n_env)
        return;
    ft_memcpy(n_env, *env, env_len * sizeof(char *));
    n_env[env_len] = ft_strdup(argv);
    n_env[env_len + 1] = NULL;
    *env = n_env;
}

int check_if_ex(char **environ, char *argv)
{
    char **existing;
    int j;

    existing = environ;
    j = 0;
    while (*existing != NULL)
    {
        while ((*existing)[j] && (*existing)[j] != '=')
            j++;
        if (ft_strncmp(*existing, argv, j) == 0 && (*existing)[j] == '=')
        {
            free(*existing);
            *existing = ft_strdup(argv);
            return (1);
        }
        existing++;
        j = 0;
    }
    return (0);
}

int if_valid(char *arg)
{
    int j;

    j = 0;
    if (!ft_isalpha(arg[0]))
        return (0);
    while (arg[j])
    {
        if (arg[j] == '=')
            return (1);
        j++;
    }
    return (0);
}

void ft_export(int argc, char **argv)
{
    extern char **environ;
    char **existing;
    int env_len;
    int i;
    int j;

    i = 1;
    j = 1;
    if (argc == 1)
    {
        while (environ[j])
        {
            printf("declare -x %s\n", environ[j]);
            j++;
        }
        return ;
    }
    while (argv[j] && argc > 2)
    {
        if (!if_valid(argv[j]))
            printf ("declare -x %s\n", argv[j]);
        j++;
    }
    while (i < argc)
    {
        if (!if_valid(argv[i])) //check if it's valid to add
        {
            i++;
            continue;
        }
        if (check_if_ex(environ, argv[i]) == 1) //check if it already exists
        {
            i++;
            continue;
        }
        else
            add_n_env(&environ, argv[i]); //add the new var
        i++;
    }
}
//