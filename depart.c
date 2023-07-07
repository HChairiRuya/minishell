/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depart.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:46:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/07 19:27:42 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    create_list(char *valeur, int type)
{
    t_nodes *node;

    node = malloc(sizeof(t_nodes));
    node->next = NULL;
    node->quotes = 0;
    node->type = type;
    node->valeur = ft_strdup(valeur);
    if (!node)
        return ;
    if (!g_all.head)
       g_all.head = node;
    else
        ft_lstaddback(g_all.head, node);
    free(valeur);
}

void    spaces(char **s)
{
    while (**s == ' ' && **s)
        (*s)++;
    // printf("space\n");
    create_list(ft_strdup(" "), SPACES);
}

void    dollar(char **s)
{
    // printf("dollar\n");
    create_list(ft_strdup("$"), DOLLAR);
    (*s)++;
}


void    pipes(char **s)
{
    // printf("pipe\n");
    create_list(ft_strdup("|"), PIPES);
    (*s)++;
}

void    double_quotes(char **s)
{
    // printf("double_quotes\n");
    create_list(ft_strdup("\""), DOUBLES_QUOTES);
    (*s)++;
}

void   single_quotes(char **s)
{
    // printf("single_quotes\n");
    create_list(ft_strdup("\'"), SINGLE_QUOTES);
    (*s)++;
}

void    redirections(char **s)
{
    char    *valeur;
    int len;

    // printf("redirection\n");
    if (**s == '<' || **s == '>')
    {
        len = 0; 
        while (**s && (**s == '<' || **s == '>'))
        {
            len++;
            (*s)++;   
        }
        if (len)
        {
            valeur = ft_substr(*s - len, 0, len);
            create_list(valeur, REDIRECT);
        }
    }
}

// void    syntax_err()
// {
    
// }

void    string(char **s)
{
    int len;
    char    *valeur;
    len = 0;
    while (**s && !ft_strchr("<>| $", **s) && (**s != '\'' && **s != '\"'))
    {
        len++;
        (*s)++;
    }
    if (len)
    {
        // printf("str : %s\n", *s - len);
        valeur = ft_substr(*s - len, 0, len);
        // printf("string %s\n", valeur);
        create_list(valeur, STRING);
    }
}


void    split_function()
{
    char    *s;

    s = g_all.line;
    while (*s)
    {
        if (*s == ' ')
            spaces(&s);
        else if (*s == '$')
            dollar(&s);
        else if (*s == '|')
            pipes(&s);
        else if (*s == '\"')
            double_quotes(&s);
        else if (*s == '\'')
            single_quotes(&s);
        else if (*s == '<' || *s == '>')
            redirections(&s);
        else
            string(&s);
    }
    check_nodes();
    chenge_type();
    // test_expand();
    voir_nodes();
}