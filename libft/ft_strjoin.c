/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:13:44 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/15 15:33:39 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	str1;
	size_t	str2;
	char	*dst;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	str1 = ft_strlen(s1);
	str2 = ft_strlen(s2) + str1 + 1;
	dst = (char *) malloc(str2);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, (char *)s1, str1 + 1);
	ft_strlcat(dst, s2, str2);
	return (dst);
}
