/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:03:56 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 09:57:03 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	ft_echo(int argc, char **argv)
{
	int	no_nl;
	int	i;

	i = 0;
	no_nl = 0;
	if (argc >= 2 && ft_strncmp(argv[1], "-n", ft_strlen("-n")) == 0)
	{
		no_nl = 1;
		argv++;
		argc--;
	}
	argv++;
	while (*argv)
	{
		printf("%s", (argv[i]));
		if (*(argv + 1))
			printf(" ");
		argv++;
	}
	if (!no_nl)
		printf("\n");
}
