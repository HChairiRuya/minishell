/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:58:41 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 16:00:59 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell_.h"

void	print_exp_error(char *argv)
{
	write(0, "minishell: ", ft_strlen("minishell: "));
	write(0, "export: ", ft_strlen("export: "));
	write (0, "`", 1);
	write(0, argv, ft_strlen(argv));
	write (0, "'", 1);
	write(0, ": ", 2);
	write(0, "not a valid identifier\n", ft_strlen("not a valid identifier\n"));
	g_all.status_val = 1;
}
