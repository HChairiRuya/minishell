/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils_III.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:05:30 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 10:11:29 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

void	end(t_path *path)
{
	close_pipes(path);
	wait_pid(path);
	free(path);
}

void	free_val(char **key_value)
{
	int	i;

	i = 0;
	while (key_value[i])
	{
		if (i != 1)
			free(key_value[i]);
		i++;
	}
	free(key_value);
}

void	ft_free_split(char **split)
{
	size_t	i;

	if (split)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}
