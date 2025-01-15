#include "../../../includes/minishell.h"

int	here_doc(t_data *data)
{
	int	pipe_fds[2];
	int	write_fd;

	if (pipe(pipe_fds) == -1)
		return (perror_return("here_doc pipe"));
	data->input.fd = pipe_fds[0];
	write_fd = pipe_fds[1];
	populate_here_doc(write_fd, data->input.value);
	return (EXIT_SUCCESS);
}

void	populate_here_doc(int write_fd, char *delimiter)
{
	char	*line;

	if (!delimiter || !*delimiter)
	{
		perror("heredoc delimiter is missing");
		close(write_fd);
		return ;
	}
	while (1)
	{
		line = readline(HERE_DOC_PROMPTE);
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			line = NULL;
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}
