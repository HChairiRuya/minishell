/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/15 16:08:16 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	suite_parsing(char **env)
{
	t_env	*env_n;

	env_n = NULL;
	change_type();
	save_env(&env_n, env);
	global_expand(env_n);
	pipe_node();
	print_data();
	// voir_nodes();
	free(g_all.line);
	g_all_clear();
	// system("leaks minishell");
}

void	ft_readline(void)
{
	g_all.line = readline("minishell> ");
	if (g_all.line == NULL)
		return ;
	add_history(g_all.line);
	split_function();
}

void	parsing(char **env)
{
	t_env	*env_n;

	env_n = NULL;
	g_all.status_val = 0;
	while (1)
	{
		ft_readline();
		if (syntaxe_err())
		{
			printf("syntaxe err \n");
			g_all_clear();
			continue ;
		}
		suite_parsing(env);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	parsing(env);
	return (0);
}
