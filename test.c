/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:13:56 by hchairi           #+#    #+#             */
/*   Updated: 2023/07/09 14:48:18 by hchairi          ###   ########.fr       */
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

// #include "minishell.h"

// // Fonction pour supprimer les nœuds contenant le caractère de guillemet double
// void removeDoubleQuoteNodes(t_nodes **head)
//  {
//     t_nodes *current = *head;
//     t_nodes* prev = NULL;
//     t_nodes* temp;
//     // Parcourir la liste chaînée
//     while (current != NULL) {
//         // Vérifier si le nœud actuel contient un guillemet double
//         if (current->valeur == "\"") {
//             temp = current;
            
//             // Mettre à jour les pointeurs pour supprimer le nœud
//             if (prev != NULL) 
//                 prev->next = current->next;
//             else 
//                 *head = current->next;
//             current = current->next;
//             free(temp); // Libérer la mémoire du nœud supprimé
//         }
//         else 
//         {
//             prev = current;
//             current = current->next;
//         }
//     }
// }

// Fonction utilitaire pour afficher la liste chaînée
// void printLinkedList(struct Node* head) {
//     struct Node* current = head;
//     while (current != NULL) {
//         printf("%c ", current->data);
//         current = current->next;
//     }
//     printf("\n");
// }

// Fonction utilitaire pour créer un nouveau nœud dans la liste chaînée
// struct Node* createNode(char data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->next = NULL;
//     return newNode;
// }

// int main() {
//     // Exemple de liste chaînée : " $ string "
//     struct Node* head = createNode('"');
//     head->next = createNode('$');
//     head->next->next = createNode('s');
//     head->next->next->next = createNode('t');
//     head->next->next->next->next = createNode('r');
//     head->next->next->next->next->next = createNode('i');
//     head->next->next->next->next->next->next = createNode('n');
//     head->next->next->next->next->next->next->next = createNode('g');
//     head->next->next->next->next->next->next->next->next = createNode('"');
    
//     printf("Avant : ");
//     printLinkedList(head);
    
//     removeDoubleQuoteNodes(&head);
    
//     printf("Après : ");
//     printLinkedList(head);
    
//     // Libérer la mémoire de la liste chaînée
//     struct Node* current = head;
//     while (current != NULL) {
//         struct Node* temp = current;
//         current = current->next;
//         free(temp);
//     }
    
//     return 0;
// }
