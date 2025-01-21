/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:49 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 23:17:07 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*build_pipes(int fd_out, int fd_in, int cmds_num)
{
	int	i;
	int	*fd_pipes;

	if (!cmds_num)
		return (0);
	fd_pipes = ft_calloc((2 * cmds_num) + 3, sizeof(int));
	if (!fd_pipes)
	{
		ft_putendl_fd(MALLOC_ERR_PIPE, 2);
		return (NULL);
	}
	fd_pipes[0] = fd_in;
	fd_pipes[1] = -1;
	fd_pipes[(2 * cmds_num)] = -1;
	fd_pipes[(2 * cmds_num) + 1] = fd_out;
	i = 0;
	while (fd_pipes && ++i < cmds_num)
	{
		if (pipe(&fd_pipes[i * 2]) < 0)
		{
			ft_putendl_fd(PIPING_ERR, 2);
			free(fd_pipes);
		}
	}
	return (fd_pipes);
}

/*Exemple avec fd_in = 0, fd_out = 1 et cmds_num = 3

Index 2 & 3 connecte cmd 1 et cmd 2
Index 4 & 5 connecte cmd 2 et cmd 3

Sortie : [ 0, -1, pipe1_read, pipe1_write, pipe2_read, pipe2_write, -1, 1 ]

fd_in -> entre standard pour cmd 1
fd_out -> sortie standar pour cmd 3*/
