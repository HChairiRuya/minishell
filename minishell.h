/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:37:08 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/12 13:13:56 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./libft/libft.h"

#define PIPES 2
#define STRING 5
#define DOLLAR 6
#define RED_OUT 7
#define RED_IN 8
#define APPEND 9
#define HERDOC 10
#define IN_FILE 11
#define OUT_FILE 12
#define SPACES 13
#define DOUBLES_QUOTES 14
#define SINGLE_QUOTES 15
// #define CMD 13
// #define ARG 14
#define S_ERR 404


typedef struct s_all
{
    char            *line;
    int             status_val;
    struct s_nodes *head;
    struct s_cmd *cmd;
} t_all ;

typedef struct  s_nodes
{
    int             quotes;
    int             type;
    char            *valeur;
    struct s_nodes  *next;
} t_nodes;

// env list
typedef struct s_env
{
    char            *s;
    struct s_env* next;
} t_env;

typedef struct s_cmd
{
    char    **data;
    int     in;
    int     out;
    struct s_cmd *next;
} t_cmd;

t_all g_all;

void    split_function();
t_env	*lstnew(char *content);
void	ft_lstaddback(t_nodes *node, t_nodes *new);
void	save_env(t_env **node, char **envr);
void    create_list(char *valeur, int type);
void    voir_nodes();
void	check_nodes();
void	change_type();

// expand
int     ft_strncmp(const char *str1, const char *str2, size_t n);
char    *get_node_value(t_env* head, char* var);
char    *global_expand(t_env *env);
void	lstaddback_env(t_env **node, t_env *new);
void	g_all_clear();
void	g_all_clear_cmd();
int     char_special(int c);
void    free_node(t_nodes *head);
void    rm_spaces();
void    link_strings();
void    link_tous();
void    pipe_node();
void    print_data();

// 
int syntaxe_err();
#endif