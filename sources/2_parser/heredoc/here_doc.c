/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:45:57 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/20 15:38:57 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int here_doc(t_data *data, char *delimiter)
{
	int	pipe_fds[2];
	int	write_fd;

	if (pipe(pipe_fds) == -1)
		return (perror_return("here_doc pipe"));
	data->input.fd = pipe_fds[0];
	write_fd = pipe_fds[1];
	if (populate_here_doc(write_fd, delimiter) == EXIT_FAILURE)
	{
		close(write_fd);
		close(data->input.fd);
		return (EXIT_FAILURE);
	}
	close(write_fd);
	return (EXIT_SUCCESS);
}

int	populate_here_doc(int write_fd, char *delimiter)
{
	char *line;

	if (!delimiter || !*delimiter)
	{
		perror("heredoc delimiter is missing");
		close(write_fd);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		line = readline(HERE_DOC_PROMPTE);
		if (!line)
			break;

		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	return (EXIT_SUCCESS);
}
