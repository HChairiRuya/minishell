/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:35:19 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/29 13:08:56 by hchairi          ###   ########.fr       */
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
		else
		{
			suite_parsing();
			if (!g_all.fde)
				execution(count_nd());
		}
		free_all();
	}
}

int	main(int ac, char **av, char **envr)
{
	(void)av;
	parsing(ac, envr);
	lstclear_env();
	return (0);
}
