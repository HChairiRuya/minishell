/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   division.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:04:05 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/13 21:29:28 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	spaces(char **s)
{
	create_list(ft_strdup(" "), SPACES);
		(*s)++;
}

void	dollar(char **s)
{
	create_list(ft_strdup("$"), DOLLAR);
	(*s)++;
}

void	pipes(char **s)
{
	create_list(ft_strdup("|"), PIPES);
	(*s)++;

}

void	double_quotes(char **s)
{
	create_list(ft_strdup("\""), DOUBLES_QUOTES);
	(*s)++;

}

void	single_quotes(char **s)
{
	create_list(ft_strdup("\'"), SINGLE_QUOTES);
	(*s)++;
}
