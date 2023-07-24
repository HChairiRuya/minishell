/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:49:21 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/24 17:01:38 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int is_valid(char *s)
{
    int i;

    i = 0;
    if (s[i] != '_' &&  !ft_isalpha(s[i]))
        return (1);
    while (s[++i] && s[i] != '=')
    {
        if (s[i] != '_' && !ft_isalnum(s[i]))
            return (1);
    }
    return (0);
}

int egal_val(t_env *node)
{
	int i;

	i = 0;
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
	int i;

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

int check_if_ex(t_env *env, char *argv)
{
    t_env *exist;
    int     j;

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
            return 1;
        }
        //     free(exist->s);
        //     free(exist);
        exist = exist->next;
    }
    return 0;
}

void _pr_exp(t_env *env)
{
    t_env *tmp;
    
    tmp = env;
	if (!env)
		return ;
    while (tmp != NULL)
    {
		if(!egal_val(tmp))
			print_n(tmp);
		else
        	printf("declare -x %s\n", tmp->s);
        tmp = tmp->next;
    }
}


void ft_export(int argc, char **argv, t_env *env)
{
	int i;

    if (argc == 1)
        _pr_exp(env);
    else
    {
		i = 1;
		while (i < argc)
		{
            if (is_valid(argv[i]))
                return ;
			else if (check_if_ex(env, argv[i]) == 1) // check if it already exists
				return ;
			else
				add_node_to_env(env, argv[i]);
			i++;
		}
    }
}
