/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:07:44 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/04 22:23:39 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char* get_node_value(t_node* head, char* var) 
{
    t_node* curr;
    
    // pour ne segfault pas si var est NULL 
    // if (!var)
    //     return (NULL);
    curr = head;
    while (curr != NULL) 
    {
        // cherche variable jusqu'a '='
        if (ft_strncmp(curr->s, var, ft_strlen(var)) == 0 && curr->s[ft_strlen(var)] == '=')
        {
            return (ft_substr(curr->s, ft_strlen(var) + 1, ft_strlen(curr->s) - ft_strlen(var)));
        }
        curr = curr->next;
    }
    return (NULL);
}


// void    dollar_solo(t_node *node)
// {
//     if (node)
//     {
//         while (node->s)
//     }
// }

int check_node(t_nodes *node)
{
    int i;

    i = 0;
    while (node->valeur[i])
    {
        if (node->valeur && node->valeur[0] == '$' /* && (node->valeur[i + 1] == '_' || node->valeur[ft_isalpha(i + 1)]) 
            && (node->valeur[ft_isalnum(i)] || node->valeur[i] == '_') */)
            return (1);
        i++;
    }
    return (0);
}

char    *global_expand()
{
    t_nodes *head = g_all.head;
    
    printf("check\n");
    while (head != NULL)
    {  
      
        if (head->type == DOLLAR && check_node(head))
        {
        //   dollar_solo(head);
            // printf("----->>>%s\n", head->next->valeur);
            return (head->next->valeur);
        }
        // if (head->type == DOUBLES_QUOTES && head->next->type == DOLLAR)
        // {
        //     return (head->next->valeur);
        // }
        head = head->next;
    }
    return (NULL);
}



// void test_expand()
// {
//     t_nodes *head = g_all.head;

//     while (head != NULL)
//     {
//         if (head->type == DOLLAR && head->next != NULL)
//         {
//             char* variable = head->next->valeur + 1; // Skip the '$' symbol
//             char* value = getenv(variable);
            
//             if (value != NULL)
//             {
//                 printf("Expanded %s: %s\n", variable, value);
//                 // Do something with the expanded value
//             }
//         }
//         head = head->next;
//     }
// }