#include "../../../includes/minishell.h"

int	here_doc(t_data *data)
{
	int	write_fd;

	g_waiting = 2;
	write_fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (write_fd == -1)
		return (perror("open"), false);
	
	// if (pipe(pipe_fds) == -1)
	// 	return (perror_return("here_doc pipe"));
	// data->input.fd = pipe_fds[0];
	// write_fd = pipe_fds[1];
	if (populate_here_doc(write_fd, data->input.value) == false)
		return (data->exit_status = 130, false);
	// printf("%d \n", data->redir->infile);
	// data->redir->infile = write_fd;
	close(write_fd);
	return (EXIT_SUCCESS);
}

// {
// 	int		fd;
// 	t_token	*last;

// 	g_waiting = 2;
// 	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (perror("open"), FALSE);
// 	if (print_in_file(fd, lim) == FALSE)
// 		return (data->status = 130, FALSE);
// 	last = ft_tokenlast(*args);
// 	ft_free(last->content);
// 	last->content = ft_strdup("<");
// 	last->type = INFILE;
// 	ft_tokenadd(args, ft_tokennew(FICHIER, ft_strdup("heredoc.tmp"), TRUE));
// 	return (TRUE);
// }

int	populate_here_doc(int write_fd, char *delimiter)
{
	char	*line;

	if (!delimiter || !*delimiter)
	{
		perror("heredoc delimiter is missing");
		close(write_fd);
		return (false);
	}
	while (1)
	{
		if (g_waiting == 3)
			return(close(write_fd), EXIT_FAILURE);
		line = readline(HERE_DOC_PROMPTE);
		if (g_waiting == 1)
			return (close(write_fd), free(line), EXIT_FAILURE);
		if (!line)
		{
			close(write_fd);
			printf("minishell: warning: here-document at line 1 ");
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
		}
		if (!line)
			break ;
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			// line = NULL;
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		// free(line);
	}
	return (close(write_fd), EXIT_SUCCESS);
}
