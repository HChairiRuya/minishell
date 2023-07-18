/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:05:24 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/17 15:45:23 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void ft_pwd()
{
	char current[256];

	if (getcwd(current, sizeof(current)))
		printf ("%s\n", current);
	else
		perror("getcwd");
}