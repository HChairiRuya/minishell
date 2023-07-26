/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+   +#+           */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:26:34 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 12:13:12 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int check_com(char *path)
{
	if (!access(path, R_OK))
	{
		if (!access(path, X_OK))
			return (1);
		else
			return (2);
	}
	return (0);
}

int iterate(t_path *path, char *args)
{
	char	**token;
	char	*full_path;
	char	*str;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	token = path->splitted;
	if (ft_strchr(args, '/') != NULL)
    {
        path->found = args;
        return (1);
    }
	while (token && token[i] != NULL)
	{
		full_path = get_full_path(token[i], args);
		if (check_com(full_path) == 1
			&& ft_strncmp(token[i], args, ft_strlen(token[i])))
		{
			path->found = full_path;
			flag = 1;
			break;
		}
		else
		{
			path->found = NULL;
			free(full_path);
		}
		i++;
	}
	return (flag);
}
