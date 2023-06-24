/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 22:37:23 by hchairi           #+#    #+#             */
/*   Updated: 2022/10/28 16:55:22 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[i] == '\0')
		return ((char *)s);
	while (s[i] && i + j < len)
	{
		while (s[i] == to_find[i] && i + j < len)
		{
			i++;
			if (to_find[i] == '\0')
				return ((char *)s);
		}
		j++;
		i = 0;
		s++;
	}
	return (0);
}
	/*
   int main()
   	{	  
   		char s[] = "future is lureing";	  
   		char to_find[] = "ure";
   	  	printf("%s\n", ft_strnstr(s, to_find, 2));
   		printf("%s", strnstr(s, to_find, 2));
   	}*/
