/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/07 19:15:27 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_readline(char **env)
{
    t_env *env_n = NULL;
    while (1)
    {
        g_all.line = readline("minishell> ");
        // if (g_all.line == NULL)
        add_history(g_all.line);
        split_function();
        save_env(&env_n, env);
        global_expand(env_n);
        g_all_clear(); // chaque fois clear nodes => (prb quand tu refaire cmd il ajoute une node (space)
    }
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    // (void)env;

    ft_readline(env);
    return 0;
}





//---------? print nodes env
        // t_node *curr = node;
        // while (curr)
        // {
        //     printf("%s\n", curr->s);
        //     curr = curr->next;
        // }
// -------> print env
    // while (env[i] != NULL)
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }
