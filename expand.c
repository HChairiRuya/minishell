/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:07:44 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/11 20:48:14 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char* get_node_value(t_env* head, char* var) 
{
    t_env* curr;
    
    if (!var)
        return (NULL);
    curr = head;
    if (!ft_strncmp(var, "$", 1))
        return (ft_strdup("1337"));
    if (!ft_strncmp(var, "?", 1))
        return (ft_itoa(g_all.status_val));
    while (curr != NULL) 
    {
        // cherche variable jusqu'a '='
        if (ft_strncmp(curr->s, var, ft_strlen(var)) == 0 && curr->s[ft_strlen(var)] == '=')
            return (ft_substr(curr->s, ft_strlen(var) + 1, ft_strlen(curr->s) - ft_strlen(var)));
        curr = curr->next;
    }
    return (NULL);
}

int check_node(t_nodes *node)
{
    int i;

    i = 0;
    if (node->valeur && (node->valeur[i] == '_' || ft_isalpha(node->valeur[i])))
        while(node->valeur && (node->valeur[++i] == '_' || ft_isalnum(node->valeur[i])))
            ;
    else
        i = 1;
    return (i);
}

void    free_node(t_nodes *head)
{
    t_nodes   *tmp;

    
    tmp = head->next; // node qui existe apres $ 
    head->next = head->next->next;
    free(tmp->valeur);
    free(tmp);
}

// void    free_node_q(t_nodes *head)
// {
//     t_nodes   *tmp;

//     tmp = head; 
//     tmp = tmp->next;
//     free(head->valeur);
//     free(head);
// }

void    rm_quotes()
{
    t_nodes *node;

    node = g_all.head;
    if (node && (node->type == DOUBLES_QUOTES || node->type == SINGLE_QUOTES))
    {
        node = g_all.head->next;
        free(g_all.head->valeur);
        free(g_all.head);
        g_all.head = node;
    }
    while (node)
    {
        if (node->next && (node->next->type == DOUBLES_QUOTES || node->next->type == SINGLE_QUOTES))
        {
            free_node(node);
        }
        else
            node = node->next;
    }
}

char    *global_expand(t_env *env)
{
    t_nodes *head;
    char    *expand_val;
    int i;
    int len;

    head = g_all.head;
    while (head != NULL)
    {
        if (head->type == DOLLAR && !head->next)
            ;
        else if (head->type == DOLLAR && head->quotes != 1 && !char_special(head->next->valeur[0]))
        {
            len = ft_strlen(head->next->valeur);
            i = check_node(head->next);
            expand_val = get_node_value(env, ft_substr(head->next->valeur, 0, i));
            head->valeur = ft_strjoin(expand_val, ft_substr(head->next->valeur, i, len));
            // printf("after----->>>  %s\n", head->valeur);   
            free_node(head); // exp "$@USER" -> @USER pour free node qui est apres dollar
        }
        // printf("node %s\n", head->valeur);
        head = head->next;
    }
    rm_quotes();
    ft_link();
    pipe_node();
    print_data();
    return (NULL);
}
