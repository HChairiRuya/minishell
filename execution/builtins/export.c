/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:49:21 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 16:00:35 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int	egal_val(t_env *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (node->s[i])
	{
		if (node->s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	print_n(t_env *node)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (node->s[i])
	{
		printf("%c", node->s[i]);
		if (node->s[i] && node->s[i] != '=' && node->s[i + 1] == '=')
		{
			printf("=\"");
			i++;
		}
		i++;
	}
	printf("\"\n");
}

int	check_if_ex(t_env *env, char *argv)
{
	t_env	*exist;
	int		j;

	exist = env;
	j = 0;
	while (argv[j] && argv[j] != '=')
		j++;
	while (exist != NULL)
	{
		if (ft_strncmp(exist->s, argv, j) == 0)
		{
			if (ft_strchr(exist->s, '=') && !ft_strchr(argv, '='))
				return (1);
			free(exist->s);
			exist->s = ft_strdup(argv);
			return (1);
		}
		exist = exist->next;
	}
	return (0);
}

void	_pr_exp(t_env *env)
{
	while (env != NULL)
	{
		if (!egal_val(env))
			print_n(env);
		else
			printf("declare -x %s\n", env->s);
		env = env->next;
	}
}

void	ft_export(int argc, char **argv, t_env *env)
{
	int	i;

	if (argc == 1)
		_pr_exp(env);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (is_valid(argv[i]))
				print_exp_error(argv[i]);
			else if (check_if_ex(env, argv[i]) == 1)
				;
			else
				add_node_to_env(env, argv[i]);
			i++;
		}
	}
}
