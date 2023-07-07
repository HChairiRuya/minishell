/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:37:08 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/07 21:46:19 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "./libft/libft.h"

#define SPACES 1
#define PIPES 2
#define DOUBLES_QUOTES 3
#define SINGLE_QUOTES 4
#define STRING 5
#define DOLLAR 6
// #define RED_SORT 7
// #define RED_ENT 8
// #define D_RED_SORT 9
// #define D_RED_ENT 10
#define REDIRECT 10
#define FILE 11
#define CMD 12


typedef struct s_all
{
    char            *line;
    char            *s;
    int             *p;
    struct s_nodes *head;
} t_all ;

typedef struct  s_nodes
{
    int             quotes;
    int             type;
    char            *valeur;
    struct s_nodes *next;
} t_nodes;

// env list
typedef struct s_env
{
    char*           s;
    struct s_env* next;
} t_env;


// typedef struct s_cmd
// {
//     char *cmd;
//     char *arg;
//     char **array;
//     char *file;
// } t_cmd;

t_all g_all;

void    split_function();
t_env	*lstnew(char *content);
void	ft_lstaddback(t_nodes *node, t_nodes *new);
void	save_env(t_env **node, char **envr);
void    create_list(char *valeur, int type);
void    voir_nodes();
void	check_nodes();
void	chenge_type();

// expand
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char* get_node_value(t_env* head, char* var);

char    *global_expand(t_env *env);
void	ft_lstaddback2(t_env **node, t_env *new);
void	g_all_clear();
int    char_special(int c);
#endif