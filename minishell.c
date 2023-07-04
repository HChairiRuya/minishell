/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/04 22:04:27 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_readline()
{
    // while (1)
    // {
        g_all.line = readline("minishell > ");
        // if (g_all.line == NULL)

        add_history(g_all.line);
        split_function();
    // }
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_node *node = NULL;
    // (void)env;
    ft_readline();
    // int i = 0;
    
    creer_nodes(&node, env);
    // t_node *curr = node;
    // while (curr)
    // {
    //     printf("%s\n", curr->s);
    //     curr = curr->next;
    // }
    char *test = get_node_value(node, global_expand());
    if (!test)
        printf("hi\n");
    else
         printf("%s\n", test);
    return 0;
}


// -------> print env
    // while (env[i] != NULL)
    // {
    //     printf("%s\n", env[i]);
    //     i++;
    // }