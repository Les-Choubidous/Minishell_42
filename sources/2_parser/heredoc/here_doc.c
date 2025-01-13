#include "../../../includes/minishell.h"

int	here_doc(t_data *data)
{
	int	pipe_fds[2];
	int	write_fd;

	if (pipe(pipe_fds) == -1)
		return (perror_return("here_doc pipe"));
	data->input.fd = pipe_fds[0];
	write_fd = pipe_fds[1];
	populate_here_doc(write_fd, data->input.value, data);
	return (EXIT_SUCCESS);
}

void	populate_here_doc(int write_fd, char *delimiter, t_data *data)
{
	char	*line;
	printf("populate here doc : %s\n", data->line);
	while (1)
	{
		//signals_interactive();
		line = readline(HERE_DOC_PROMPTE);
		//signals_non_interactive();
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			line = NULL;
			break ;
		}
		// if (expand_string(&line, data) == EXIT_FAILURE)
		// {
		// 	free(line);
		// 	break ;
		// }
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}
