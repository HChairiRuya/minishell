/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:37:08 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/26 10:15:20 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define PIPES 1
# define STRING 2
# define DOLLAR 3
# define EXPANDED 4
# define RED_OUT 5
# define RED_IN 6
# define APPEND 7
# define HERDOC 8
# define SPACES 9
# define OUT_FILE 10
# define IN_FILE 11
# define D_Q 12
# define S_Q 13
# define S_ERR 404

typedef struct s_all
{
	char				*line;
	int					status_val;
	int					k;
	int					h;
	int					dup_z;
	int					dup_o;
	struct sigaction	act;
	struct s_nodes		*head;
	struct s_env		*env;
	struct s_cmd		*cmd;
	char				**envr;
	pid_t				*child;
}	t_all;

typedef struct s_nodes
{
	int				check;
	int				quotes;
	int				type;
	char			*valeur;
	struct s_nodes	*next;
}	t_nodes;

typedef struct s_env
{
	char			*s;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**data;
	int				in;
	int				out;
	struct s_cmd	*next;
}	t_cmd;

t_all	g_all;

void	split_function(void);
t_env	*ft_lstnew(char *content);
void	ft_lstaddback(t_nodes *node, t_nodes *new);
void	save_env(t_env **node, char **envr);
void	create_list(char *valeur, int type);
void	voir_nodes(void);
void	check_nodes(void);
void	change_type(void);
void	spaces(char **s);
void	dollar(char **s);
void	pipes(char **s);
void	double_quotes(char **s);
void	single_quotes(char **s);
int		check_redirect(char *valeur);
void	redirections(char **s);
void	string(char **s);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*get_node_value(t_env *head, char *var);
char	*global_expand(t_env *env);
void	lstaddback_env(t_env **node, t_env *new);
void	g_all_clear(void);
void	g_all_clear_cmd(void);
int		char_special(int c);
void	free_node_exp(t_nodes *head);
void	rm_spaces(void);
void	link_strings(void);
void	link_tous(void);
void	pipe_node(t_env *env);
void	print_data(void);
void	free_space(t_nodes **head);
t_nodes	*lstnew_expand(char *content);
int		syntaxe_err(void);
void	delete_node_expanded(t_nodes *del, t_nodes *save);
void	lstaddback_save(t_nodes **node, t_nodes *new);
t_nodes	*ft_lstlast(t_nodes *lst);
void	free_space(t_nodes **head);
void	save_list(t_nodes **node, char *val);
int		check_space(char *value);
void	redirect(t_cmd *cmd, t_env *env);
void	lstclear_env(void);
t_nodes	*get_next(t_nodes *node);
void	expand_herdoc(void);
void	depart_seg(void);
void	initial(char **envr);
void	ft_readline(void);
void	suite_parsing(void);
void	herdoc(t_nodes	*node, t_cmd *cmd, char *del, t_env *env);
void	free_all(void);
#endif

// void print_err(t_cmd *cmd)
// {
// 	write(0, "minishell", ft_strlen("minishell"));
// 	write(0, ": ", 2);
// 	perror(cmd->data[0]);
// 	exit (127);
// }