#include "minishell.h"

int	cmd_count(t_commands *cmds)
{
	int			i;
	t_commands	*ptr;

	i = 0;
	ptr = cmds;
	while (ptr && ++i)
		ptr = ptr->next;
	return (i);
}

int	executer(t_data *data)
{
	int		cmds_num;
	int		*fd_pipes;
	pid_t	*pid;

	cmds_num = cmd_count(data->command);
	pid = (pid_t *)ft_calloc(cmds_num, sizeof(pid_t));
	if (!pid)
		return (EXIT_FAILURE);
	fd_pipes = build_pipes(data->output.fd, data->input.fd, cmds_num);
	if (!fd_pipes)
		return (free(pid), EXIT_FAILURE);
	data->pid = pid;
	execute_pipeline(fd_pipes, pid, data);
	free(fd_pipes);
	free(pid);
	pid = NULL;
	return (EXIT_SUCCESS);
}
