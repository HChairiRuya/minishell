/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:39:01 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/17 13:01:46 by fbelahse         ###   ########.fr       */
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

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while ((s1[i] != '\0' || s2[i] != '\0') && s1[i] == s2[i])
// 	{
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }

char *get_full_path(char *token, char *args)
{
    char *first;
    char *second;

    first = ft_strcat(token, "/");
    second = ft_strcat(first, args);
    return (second);
}
