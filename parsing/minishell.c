/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 13:01:36 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void	suite_parsing(char **env)
{
	t_env	*env_n;

	env_n = NULL;
	change_type();
	save_env(&env_n, env);
	global_expand(env_n);
	pipe_node(env_n);
	// print_data();
	// voir_nodes();
	// lstclear_env(env_n);
	// system("leaks minishell");
}
int	count_ac()
{
	t_nodes	*node;
	int	count;

	count = 0;
	node = g_all.head;
	while (node && node->type != PIPES)
	{
		if (node && node->type == STRING)
			count++;
		node = node->next;
	}
	return (count);
}

int	count_nd()
{
	t_cmd	*node;
	int	count;

	count = 0;
	node = g_all.cmd;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

void	ft_readline(void)
{
	g_all.line = readline("minishell> ");
	if (g_all.line == NULL)
		return ;
	add_history(g_all.line);
	split_function();
}

void	initial(void)
{
	g_all.status_val = 0;
	g_all.k = 0;
	g_all.h = 0;
	g_all.dup_z = dup(0);
	g_all.dup_o = dup(1);
}

void	parsing(int argc, char **env)
{
	initial();
	while (1)
	{
		depart_seg();
		ft_readline();
		if (syntaxe_err())
		{
			printf("syntaxe err \n");
			free(g_all.line);
			g_all_clear();
			continue ;
		}
		suite_parsing(env);
		pipin(count_nd());
		free(g_all.line);
		g_all_clear();
		g_all_clear_cmd();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	parsing(ac, env);
	return (0);
}
