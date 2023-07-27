/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:16:23 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/26 21:44:37 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	suite_parsing(void)
{
	change_type();
	global_expand(g_all.env);
	pipe_node(g_all.env);
	// print_data();
	// voir_nodes();
	// system("leaks minishell");
}

void	ft_readline(void)
{
	g_all.line = readline("minishell> ");
	if (!g_all.line)
	{
        printf("exit\n");	
		ft_exit();
	}
	if (g_all.line == NULL)
		return ;
	if (g_all.line[0])
		add_history(g_all.line);
	split_function();
	// voir_nodes();
}

void	initial(char **envr)
{
	g_all.status_val = 0;
	g_all.k = 0;
	g_all.h = 0;
	g_all.dup_z = dup(0);
	g_all.dup_o = dup(1);
	g_all.envr = envr;
	save_env(&g_all.env, envr);
}
