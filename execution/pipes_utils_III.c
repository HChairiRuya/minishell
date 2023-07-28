/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils_III.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelahse <fbelahse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:05:30 by fbelahse          #+#    #+#             */
/*   Updated: 2023/07/28 13:14:37 by fbelahse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_.h"

int hi(t_cmd *cmd, t_path *path)
{
	if (if_bt_found(cmd->data) && count_nd() == 1)
	{
        builtins(count_ac(), cmd->data);
		free(path);
		return (0);
	}
	if (cr_pipes(path) == 1)
	{
		perror("cr_pipes");
		// ft_free_split(path->splitted); //free test split
		return (1);
	}
	return (1);
}

void end(t_path *path)
{
	close_pipes(path);
	wait_pid(path);
	free(path);
}

// void	ft_echo(int argc, char **argv)
// {
// 	int	no_nl;
// 	int	i;
//     char *n;

// 	i = 1;
// 	no_nl = 0;

//     n = NULL;
//     while (argv[i])
//     {
//         n = ft_strchr(argv[i], 'n');
//         if (argc >= 2 && ft_strcmp_ch(argv[i][0], '-') == 0
//         && argv[i][0] == '-' && argv[i][1] == 'n')
//         {
//             if (ft_cmp(n) == 1)
//                 break;
//             else
//             {
//                 no_nl = 1;
//                 argv++;
//                 argc--;
//             }
//             continue;
//         }
//         else
//             break;
//         i++;
//         n = NULL;
//     }
//     argv++;
//     i = 0;
//     while (argv[i])
//     {
//         printf("%s", argv[i]);
//         if (argv[i + 1])
//             printf(" ");
//         i++;
//     }
//     if (!no_nl)
//         printf("\n");
// }
