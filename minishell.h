/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:37:08 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/04 22:02:51 by hchairi          ###   ########.fr       */
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

typedef struct s_node 
{
    char*           s;
    struct s_node* next;
} t_node;


// typedef struct s_cmd
// {
//     char *cmd;
//     char *arg;
//     char **array;
//     char *file;
// } t_cmd;

t_all g_all;

void    split_function();
t_node	*lstnew(char *content);
void	ft_lstaddback(t_nodes *node, t_nodes *new);
void   creer_nodes(t_node **node, char **envr);
void    create_list(char *valeur, int type);
void    voir_nodes();
void	check_nodes();
void	chenge_type();
void	test_expand();

// expand
int	ft_strncmp(const char *str1, const char *str2, size_t n);
char* get_node_value(t_node* head, char* var);

char    *global_expand();

void	ft_lstaddback2(t_node **node, t_node *new);
#endif