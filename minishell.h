/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:37:08 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/23 16:39:34 by hchairi          ###   ########.fr       */
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

typedef struct s_cmd
{
    char **array;
    char *file;
} t_cmd;

t_all g_all;

void    split_function();
void	ft_lstaddback(t_nodes *node, t_nodes *new);
void    create_list(char *valeur, int type);
void    voir_nodes();
void	check_nodes();
#endif