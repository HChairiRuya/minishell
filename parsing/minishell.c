/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/26 10:38:50 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int	count_ac(void)
{
	t_nodes	*node;
	int		count;

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

int	count_nd(void)
{
	t_cmd	*node;
	int		count;

	count = 0;
	node = g_all.cmd;
	while (node)
	{
		count++;
		node = node->next;
	}
	return (count);
}

void	parsing(int argc, char **envr)
{
	initial(envr);
	while (1)
	{
		depart_seg();
		ft_readline();
		if (syntaxe_err())
		{
			g_all.status_val = 258;
			printf("syntaxe err \n");
			free(g_all.line);
			g_all_clear();
			continue ;
		}
		suite_parsing();
		int exit_status = pipin(count_nd());
		free_all();
	}
}

int	main(int ac, char **av, char **envr)
{
	(void)av;
	parsing(ac, envr);
	return (0);
}
