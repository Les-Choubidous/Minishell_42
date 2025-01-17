#include "minishell.h"

int	close_fd(int *fd)
{
	if (*fd <= 2)
		return (EXIT_SUCCESS);
	if (close(*fd) == -1)
	{
		ft_putendl_fd(FD_ERR_CLOSE, 2);
		return (EXIT_FAILURE);
	}
	*fd = -1;
	return (EXIT_SUCCESS);
}

int finalize_child_processes(pid_t *pid, int num, t_data *data, int *fd_pipes)
{
    int i;
    int exit_code;

    if (!pid || num <= 0 || !fd_pipes)
        return (EXIT_FAILURE);
    for (i = 0; i < num; i++)
	{
        if (pid[i] > 0)
		{
            waitpid(pid[i], &exit_code, 0);

            if (i == num - 1 && WIFEXITED(exit_code))
                data->exit_status = WEXITSTATUS(exit_code);
            else if (i == num - 1 && WIFSIGNALED(exit_code))
                data->exit_status = WTERMSIG(exit_code) + 128;

            close_fd(&fd_pipes[i * 2]);
            close_fd(&fd_pipes[i * 2 + 3]);
        }
    }
    close_unused_fd(fd_pipes, num * 2 + 3);
    return (EXIT_SUCCESS);
}

int close_unused_fd(int *fd_pipes, int len)
{
    int i;

    if (!fd_pipes || len <= 0)
        return (EXIT_FAILURE);

    for (i = 0; i < len; i++) 
	{
        if (fd_pipes[i] > 2)
		{
            close(fd_pipes[i]);
            fd_pipes[i] = -1;
        }
    }
    return (EXIT_SUCCESS);
}
