/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:54:33 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/07 21:45:59 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_lstaddback(t_nodes *node, t_nodes *new)
{
	if (!node || !new)
		return ;
	while (node->next)
		node = node->next;
	node->next = new;
}

void	g_all_clear()
{
	t_nodes	*tmp;
	t_nodes	*tmp_next;

	if (!g_all.head)
		return ;
	tmp = g_all.head;
	while (tmp)
	{
		tmp_next = tmp->next;
		free (tmp->valeur);
		free (tmp);
		tmp = tmp_next;
	}
	g_all.head = NULL;
}

int    char_special(int c)
{
    if (c == '-' || c == '+' || c == '/' || c == '^'
        || c == '%' || c == '.' || c == ',' || c == '=')
        return (1);
    return (0);
}
// char	*ft_strjoin(char *s1, char c)
// {
// 	char	*s3;
// 	int		i;

// 	if (!s1)
// 	{	
// 		s1 = malloc(1);
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	else
// 	{
// 		i = ft_strlen(s1);
// 		s3 = malloc(sizeof(char) * (i + 2));
// 		if (!s3)
// 			return (NULL);
// 		i = -1;
// 		while (s1[++i])
// 		{
// 			s3[i] = s1[i];
	
// 		}
// 	}
// 	s3[i++] = c;
// 	s3[i] = '\0';
// 	// free(s1);
// 	return (s3);
// }



// int main()
// {
// 	char *s= "hello how are you";
// 	printf("%s\n", string(s));
// }


// char *string(char *s)
// {
//     int i;
//     int j;
//     int len;

//     i = 0;
//     j = 0;
//     while (s[j])
//     {
// 		while (s[j] == ' ')
// 			j++;
// 		i = j;
//         while (s[i] && s[i] != ' ')
// 		{
// 			len++;
// 			i++;
// 		}
// 		ft_substr(s, j, len);
// 		len = 0;
// 		j = i;
//     }
// 	return (NULL);
// }

// int main()
// {
// 	char *s = "  1337 future is loading";
// 	printf("%s\n", string(s));
// }

