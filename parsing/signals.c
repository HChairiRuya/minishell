/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:51:12 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/28 19:48:49 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_ctrl(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGINT)
	{
		if (!g_all.k)
		{
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			close(0);
			printf("\n");
			g_all.h = 1;
		}
	}
}

void	depart_seg(void)
{
	sigemptyset(&g_all.act.sa_mask);
	g_all.act.sa_handler = &sig_ctrl;
	g_all.act.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &g_all.act, NULL);
	sigaction(SIGINT, &g_all.act, NULL);
}
