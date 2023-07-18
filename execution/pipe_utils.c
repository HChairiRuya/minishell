/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:35:20 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/18 16:52:28 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void for_last(t_path *path, int fd)
{
	if (dup2(path->pipes_fd[fd][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
}