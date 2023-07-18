/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:26:41 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/18 20:50:44 by fbelahse         ###   ########.fr       */
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
	char **all_args;
	char *found;
	int (*pipes_fd)[2];
	int n_pipes;
	int n_args;
}t_path;


char	*ft_strcat(char *dst, const char *src);
char	*get_full_path(char *token, char *args);
int		forking(const char *cmd, char **args);
int		iterate(t_path *path, char *args);
int 	check_com(char *path);
int		ft_strcmp(char *s1, char *s2);
int		executin(t_cmd *cmd, char **argv);
void	ft_echo(int argc, char **argv);
void	ft_pwd();
void	for_last(t_path *path, int fd);
void for_last(t_path *path, int fd);
int cr_pipes(t_path *path);
void close_pipes(t_path *path);
void duplicate(int fd, t_path *path, int last);
int forking_for_pipe(t_path *pt, t_cmd *cmd, int i);
int pipin(int argc);
int start(t_path *pt);
int	ft_count(t_nodes *node);

#endif