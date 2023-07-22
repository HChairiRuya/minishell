/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:39:01 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/22 13:13:23 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

char	*ft_strcat(char *dst, const char *src)
{
    int	i;
    int	len;

    i = 0;
    len = ft_strlen(dst);
    while (src[i])
    {
        dst[len + i] = src[i];
        i++;
    }
    dst[len + i] = '\0';
    return (dst);
}

char *get_full_path(char *token, char *args)
{
    char *first;
    char *second;

    first = ft_strjoin(token, "/", 0);
    second = ft_strjoin(first, args, 1);
    return (second);
}
