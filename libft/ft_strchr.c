/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:50:14 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/22 16:08:59 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c1;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	c1 = (char )c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == c1)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == c1)
		return ((char *)&str[i]);
	return (NULL);
}
