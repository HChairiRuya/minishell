/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:16:55 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/29 16:28:55 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	to_unset(t_env *env, char *arg)
{
	t_env	*tmp;
	
	tmp = NULL;
	while (env)
	{
		if(!ft_strncmp(arg, env->s, ft_strlen(arg)))
		{
			if (env->s[ft_strlen(arg)] == '=')
			{
				if (tmp)
					tmp->next = env->next;
				else
					g_all.env = g_all.env->next;
				free(env->s);
				env->s = NULL;
				free(env);
				env = NULL;
				break ;
			}
		}
		tmp = env;
		env = env->next;
	}
}

void	ft_unset(char **argv, t_env **env_list)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		to_unset(*env_list, argv[i]);
		i++;
	}
	if (!g_all.env)
		g_all.env = NULL;
}
