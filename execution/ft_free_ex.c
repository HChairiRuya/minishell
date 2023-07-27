/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:55:51 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/25 20:19:56 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

// Function to free a t_path struct
void free_t_path(t_path *path) 
{
    // Free the dynamically allocated char pointers in 'splitted'
    // if (path->splitted != NULL) {
    //     for (int i = 0; i < path->n_args; i++) {
    //         free(path->splitted[i]);
    //     }
    //     free(path->splitted);
    // }

    // Free the dynamically allocated char pointers in 'all_args'
    // printf("%d\n", path->n_args);
    // int i = 0;
    // if (path->all_args != NULL) {
    //     while (path->all_args[i])
    //     {
    //     free(path->all_args[i]);
    //     i++;
    //     }
    //     free(path->all_args);
    // }

    // Free the dynamically allocated memory for 'found'
    // free(path->found);

    // Free the dynamically allocated memory for 'pipes_fd'
    if (path->pipes_fd != NULL) {
        free(path->pipes_fd);
    }

    // Finally, free the memory allocated for the t_path struct itself
    // free(path);
}