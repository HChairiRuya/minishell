/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/19 11:31:04 by hchairi          ###   ########.fr       */
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
	pipe_node();
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
	while (node)
	{
		count++;
		node = node->next;
	}
	// printf(" count %d\n", count);
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

void builtinss(int argc, char **argv)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(argv[0], "echo") == 0)
		ft_echo(argc, argv);
}

void	ft_readline(void)
{
	g_all.line = readline("minishell> ");
	if (g_all.line == NULL)
		return ;
	add_history(g_all.line);
	split_function();
}

void	parsing(int argc, char **env)
{
	// int count;

	g_all.status_val = 0;
	while (1)
	{
		ft_readline();
		if (syntaxe_err())
		{
			printf("syntaxe err \n");
			free(g_all.line);
			g_all_clear();
			continue ;
		}
		suite_parsing(env);
		// count = count_ac();
		// printf ("counntt: %d\n", count);
		builtinss(argc, g_all.cmd->data);
		pipin(count_nd());
		// executin(g_all.cmd, env);
		// print_data();
		free(g_all.line);
		g_all_clear();
		g_all_clear_cmd();
		// count = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	// (void)ac;
	// (void)av;
	parsing(ac, env);
	return (0);
}
