/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:03:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 14:54:20 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

int	ft_strcmp_ch(char c, char target)
{
	if (c == target)
		return (0);
	else
		return (1);
}

int	ft_cmp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	pr_arg(char **argv, int no_nl)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!no_nl)
		printf("\n");
}

void	change(int *no_nl, char ***argv, int *argc)
{
	*no_nl = 1;
	(*argv)++;
	(*argc)--;
}

void	ft_echo(int argc, char **argv)
{
	int		no_nl;
	int		i;
	char	*n;

	i = 1;
	no_nl = 0;
	n = NULL;
	while (argv[i])
	{
		n = ft_strchr(argv[i], 'n');
		if (argc >= 2 && ft_strcmp_ch(argv[i][0], '-') == 0
		&& argv[i][0] == '-' && argv[i][1] == 'n')
		{
			if (ft_cmp(n) == 1)
				break ;
			else
				change(&no_nl, &argv, &argc);
			continue ;
		}
		else
			break ;
		i++;
	}
	argv++;
	pr_arg(argv, no_nl);
}
