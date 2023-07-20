/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:49:21 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/20 20:29:11 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int count_env(char **env)
{
	int count;

	count = 0;
    while (*env != NULL)
	{
        count++;
        env++;
    }
	return (count);
}

void ft_export(int argc, char **argv)
{
    extern char **environ;
    char **env_ = environ;
    char *curr = NULL;
    char **exported = NULL;
    int exp_len = 0;
    int i = 1;

    while (i < argc)
    {
        env_ = environ;
        if (ft_isalpha(argv[i][0]) == 0)
        {
            i++;
            continue;
        }
        int found = 0;
        while (*env_ != NULL)
        {
            curr = *env_;
            char *stt = ft_strchr(argv[i], '=');
            printf ("HERE!!!%s\n", stt);
            if ((ft_strncmp(curr, argv[i], ft_strlen(argv[i])) == 0))
            {
                found = 1;
                break;
            }
            env_++;
        }
        if (!found)
        {
            char *new_var = ft_strdup(argv[i]);
            if (!new_var)
            {
                perror("strdup");
                return;
            }
            int j = 0;
            while (argv[i][j])
            {
                if (argv[i][j] == '=')
                    break;
                j++;
            }
            if (argv[i][j] != '=')
            {
                i++;
                continue;
            }
            char *new = ft_strdup(argv[i]);
            if (!new)
            {
                perror("strdup");
                return;
            }
            exp_len = count_env(environ);
            exported = malloc((exp_len + 2) * sizeof(char *));
            if (!exported)
            {
                perror("malloc");
                free(new);
                return;
            }
            int k = 0;
            while (k < exp_len)
            {
                exported[k] = environ[k];
                k++;
            }
            exported[exp_len] = new;
            exported[exp_len + 1] = NULL;
            environ = exported;
        }
        i++;
    }
}
