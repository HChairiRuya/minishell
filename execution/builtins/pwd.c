/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:05:24 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/25 10:03:10 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	ft_pwd(void)
{
	char	current[256];

	if (getcwd(current, sizeof(current)))
		printf ("%s\n", current);
	else
		perror("getcwd");
}
