/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:18:46 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 19:57:54 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int cr_pipes(t_path *path)
{
    int i;

    i = 0;
    path->pipes_fd = malloc(path->n_pipes * sizeof(int *));
    if (path->pipes_fd == NULL)
        return (1);
    while (i < path->n_pipes)
    {
        if (pipe(path->pipes_fd[i]) == -1)
        {
            perror("pipe");
            return (1);
        }
        i++;
    }
    return (0);
}

void print_err(t_cmd *cmd, char *args)
{
	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	if (check_com(args) == 2)
	{
		perror(cmd->data[0]);
		exit (126);
	}
	else
	{
		write (2, cmd->data[0], ft_strlen(cmd->data[0]));
		write (2, ": ", 2);
		write (2, "command not found\n", ft_strlen("command not found\n"));
		exit (127);
	}
}

char *get_full_path(char *token, char *args)
{
    char *first;
    char *second;

    first = ft_strjoin(token, "/", 0);
    second = ft_strjoin(first, args, 1);
    return (second);
}
