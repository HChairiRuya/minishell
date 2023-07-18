/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:11:25 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/18 16:50:48 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_nodes	*get_next(t_nodes *node)
{
	while (node && (node->type == SPACES 
            || node->type == DOUBLES_QUOTES 
            ||  node->type == SINGLE_QUOTES))
		node = node->next;
	return (node);
}

// void	herdoc()
// {
// 	t_nodes	*node;
// 	char	*l;
// 	char	*save;
// 	int		i;

// 	node = g_all.head;
// 	save = NULL;
// 	int fds[2];

// 	pipe(fds);
// 	if (node && node->next && node->type == HERDOC && get_next(node->next)->type == IN_FILE)
// 	{
// 		while (1)
// 		{
// 			i = 0;
// 			l = readline("");
// 			if (!l)
// 				return ;
// 			save = malloc((ft_strlen(l) + 1) * sizeof(char));
// 			if (!save)
// 			{
// 				free(l);
// 				return;
// 			}
// 			// ft_strcpy(save, l);
// 			save = ft_strjoin(save, l, 0);
// 			save = ft_strjoin(save, "\n", 0);
// 			printf("save  : %s\n", save);
// 			printf("l  : %s\n", l);
// 			printf("check %s\n", get_next(node->next)->valeur);
// 			if (!ft_strcmp(l, get_next(node->next)->valeur))
// 			{
// 				free(save);	
// 				free(l);	
// 				return ;
// 			}
// 			free(l);
// 		}
// 	}
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void herdoc(t_cmd * cmd, char *del)
{
    char *l;
    int pipefd[2];

    printf("del %s\n", del);
    if (pipe(pipefd) == -1) 
	{
        perror("pipe");
        return;
    }
    printf("pipe %d\n", pipefd[0]);
    cmd->in = pipefd[1];
    while (1) 
    {
        l = readline("");
        write(pipefd[1], l, ft_strlen(l)); // Write the line to the pipe
        write(pipefd[1], "\n", 1); // Write newline to the pipe
        if (!ft_strcmp(l, del))
    	{
    		free(l);	
    		return ;
    	}
        free(l);
    }
    close(pipefd[0]); // Close the read end of the pipe
}


void	redirect_cases(t_nodes *node, t_cmd *cmd)
{
	if (node->type == RED_OUT)
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = open(get_next(node->next)->valeur, O_RDWR | O_CREAT, 0664);
	}
	if (node->type == APPEND)
	{
		if (cmd->out != 1)
			close(cmd->out);
		cmd->out = open(get_next(node->next)->valeur,
				O_RDWR | O_CREAT | O_APPEND, 0664);
	}
	if (node->type == RED_IN)
	{
		if (cmd->in != 0)
			close(cmd->in);
		cmd->in = open(get_next(node->next)->valeur, O_RDWR, 0664);
	}
	if (node->type == HERDOC)
		herdoc(cmd, get_next(node->next)->valeur);
}

void	redirect(t_cmd *cmd)
{
	t_nodes	*node;

	node = g_all.head;
	while (node)
	{
		if (node->type >= 5 && node->type <= 8)
			redirect_cases(node, cmd);
		else if (node->type == PIPES && cmd->next)
			cmd = cmd->next;
		node = node->next;
	}
}
