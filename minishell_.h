/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:26:41 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/17 14:53:02 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HE
# define MINISHELL_HE

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "./parsing/minishell.h"
// #include "./libft/libft.h"

typedef struct s_path
{
	char **splitted;
	int	**pipes_fd;
	char **all_args;
	char *found;
	int n_pipes;
	int n_args;
}t_path;


char	*ft_strcat(char *dst, const char *src);
char	*get_full_path(char *token, char *args);
int forking(const char *cmd, char **args);
int		iterate(t_path *path, char *args);
int		check_com(char *path, char *cmd);
int		ft_strcmp(char *s1, char *s2);
int executin(t_cmd *cmd, char **argv);
void	for_last(t_path *path, int fd);

#endif