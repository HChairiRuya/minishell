/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:26:41 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/27 15:55:00 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_HE
# define MINISHELL_HE

# include <stdio.h>
#include <sys/wait.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include "./parsing/minishell.h"
// #include "./libft/libft.h"

typedef struct	s_path
{
	char	**splitted;
	char	*found;
	int		(*pipes_fd)[2];
	int		n_pipes;
	int		n_args;
}	t_path ;

char	*ft_strcat(char *dst, const char *src);
char	*get_full_path(char *token, char *args);
int		forking(const char *cmd, char **args);
int		iterate(t_path *path, char *args);
int check_com(char *path);
int		ft_strcmp(char *s1, char *s2);
int		executin(t_cmd *cmd, char **argv);
void	ft_echo(int argc, char **argv);
void	ft_pwd();
void	for_last(t_path *path, int fd);
void for_last(t_path *path, int fd);
int cr_pipes(t_path *path);
void close_pipes(t_path *path);
void forking_for_pipe(t_path *pt, t_cmd *cmd, int i);
int execution(int argc);
int start(t_path *pt);
int	ft_count(t_nodes *node);
void ft_env();
void	save_env(t_env **node, char **envr);
t_env	*ft_lstnew(char *content);
int	count_ac();
int	count_nd();
void builtins(int argc, char **argv);
int if_bt_found(char **argv);
void ft_cd(char **argv, t_env *env);
void ft_export(int argc, char **argv, t_env *env);
void ft_exit_e(int argc, char **argv);
int set_ex_s(int val);
void ft_unset(char **argv, t_env **env_list);
void add_node_to_env(t_env *env, char *s);
void _pr_exp(t_env *env);
void pr_env(t_env *env);
void ft_exit_e(int argc, char **argv);
int	count_ac(void);
void pr_err(char *args);
void dup_middle(t_path *path, int fd);
void dup_end(t_path *path, int fd);
void dup_middle(t_path *path, int fd);
void dup_first(t_path *path, int fd);
void free_pipes(t_path *path);
int cr_pipes(t_path *path);
void print_err(t_cmd *cmd, char *args);
char *find_path(t_env *env);
void replace(t_env *env, char *value);
void pr_err_no_file(char *args);
void pr_err_not_a_dir(char *args);

#endif