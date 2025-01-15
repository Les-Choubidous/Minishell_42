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

int	close_unused_fd(int *fd_pipes, int pos, int keep, int len)
{
	int	i;
	int	*ptr;
	int	fd_in;
	int	fd_out;

	if (!fd_pipes || pos < 0 || len == 0 || keep > FDX_RW || keep < FDX_NONE)
		return (EXIT_FAILURE);
	i = 1;
	ptr = fd_pipes;
	fd_in = -1;
	fd_out = -1;
	if (keep == FDX_RW || keep == FDX_OR)
		fd_in = pos;
	if (keep == FDX_RW || keep == FDX_OW)
		fd_out = pos + 3;
	while (++i < len)
	{
		if (i != fd_in && fd_out && close_fd(&ptr[i]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
