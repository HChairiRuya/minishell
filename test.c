/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:13:56 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/19 20:10:32 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ls -l -p -o file1 file2 > resul1 > result2 > resul3
// typedef t_type
// {
//     char *cmd;          //ls
//     char *option;       // -l -p -o 
//     char **arg;            // file1 file2
//     char **in_file;         // 
//     char **out_file;
// }
// //env
// typedef t_env{
//     char *name;
//     char *value;
//     next;
// }

// #include <stdio.h>

// int main(int ac, char **av, char **env)
// {
//     int i;
//     i = 0;
    
//     while (env[i])
//     {
//         printf("%s\n", env[i]);
//         i++;
//     }
// }

// strtock separer une chaine par des separators 
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// int main() {

//     // La chaine de caractères à traiter.
//     char str[] = "- Voici une phrase avec quelques séparateurs ! -";
//     // La définitions de séparateurs connus.
//     const char * separators = " ,.-!";

//     // On cherche à récupérer, un à un, tous les mots (token) de la phrase
//     // et on commence par le premier.
//     char * strToken = strtok ( str, separators );
//     while ( strToken != NULL ) {
//         printf ( "%s\n", strToken );
//         // On demande le token suivant.
//         strToken = strtok ( NULL, separators );
//     }
//     return EXIT_SUCCESS;
// }

