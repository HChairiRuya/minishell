/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:51:12 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 11:56:10 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void    sig_ctrl(int sig)
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

void    depart_seg()
{
    sigemptyset(&g_all.act.sa_mask);
    g_all.act.sa_handler = &sig_ctrl;
    g_all.act.sa_flags = SA_RESTART; // act_restart
    sigaction(SIGQUIT, &g_all.act, NULL);
    sigaction(SIGINT, &g_all.act, NULL);
}












// void    reprompt(void)
// {
//     ft_putchar_fd('\n', 1);
//     rl_on_new_line();
//     // rl_replace_line("", 0);
//     rl_redisplay();
// }

// void    kill_shell(void)
// {
//     ft_putstr_fd("exit\n", 1);
//     exit(g_all.status_val);
// }

// void    ctrl_handler(int sigint)
// {
//     if (sigint == SIGINT)
//         reprompt();
// }

// void    init_signal_handler(void)
// {
//     signal(SIGINT, ctrl_handler);
//     signal(SIGQUIT, SIG_IGN);
// }

// void    init_sig_handler_child(void)
// {
//     signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
//     signal(SIGTSTP, SIG_DFL);
// }
