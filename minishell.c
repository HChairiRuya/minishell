/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/22 16:55:04 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_readline()
{
    while (1)
    {
        g_all.line = readline("minishell > ");
        // if (g_all.line == NULL)

        add_history(g_all.line);
        split_function();
    }
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    ft_readline();    
    return 0;
}