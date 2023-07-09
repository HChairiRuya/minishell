/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depart.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:46:21 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/09 20:06:04 by hchairi          ###   ########.fr       */
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
    // while (**s == ' ' && **s)
    //     (*s)++;
    create_list(ft_strdup(" "), SPACES);
        (*s)++;
}

void    dollar(char **s)
{
    create_list(ft_strdup("$"), DOLLAR);
    (*s)++;
}


void    pipes(char **s)
{
    create_list(ft_strdup("|"), PIPES);
    (*s)++;
}

void    double_quotes(char **s)
{
    create_list(ft_strdup("\""), DOUBLES_QUOTES);
    (*s)++;
}

void   single_quotes(char **s)
{
    create_list(ft_strdup("\'"), SINGLE_QUOTES);
    (*s)++;
}


int check_redirect(char *valeur)
{
    if (!ft_strcmp(valeur, "<"))
       return (RED_IN);
    else if (!ft_strcmp(valeur, "<<"))
       return (HERDOC);
    else if (!ft_strcmp(valeur, ">"))
       return (RED_OUT);
    else if (!ft_strcmp(valeur, ">>"))
       return (APPEND);
    // else if (!ft_strcmp(valeur, "<>"))
    //     return ()
    else
        return (S_ERR);
}

void    redirections(char **s)
{
    char    *valeur;
    int len;

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
            create_list(valeur, check_redirect(valeur));
        }
    }
}

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
        create_list(valeur, STRING);
    }
}

void    free_space(t_nodes **head)
{
    t_nodes   *tmp;

    tmp = g_all.head;
    g_all.head = g_all.head->next;
    free(tmp->valeur);
    free(tmp);
    *head = g_all.head;
}

void    rm_spaces()
{
    t_nodes *node;

    node = g_all.head;
    while (node != NULL)
    {
        if (node == g_all.head && node->type == SPACES && node->quotes == 0)
        {
            while (node && node->type == SPACES)
                free_space(&node); 
        }
        if ((node && node->next && node->next->type == SPACES && node->next->quotes == 0))
        {  
            node = node->next; //node = " "
            while (node->next && node->next->type == SPACES)
                free_node(node);
        }
        if (node)
            node = node->next;
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
    change_type();
    rm_spaces();
}