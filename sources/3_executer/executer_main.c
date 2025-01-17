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

	cmds_num = cmd_count(data->command);
	data->pid = (pid_t *)ft_calloc(cmds_num, sizeof(pid_t));
	if (!data->pid)
		return (EXIT_FAILURE);
	data->fd_pipes = build_pipes(data->output.fd, data->input.fd, cmds_num);
	if (!data->fd_pipes)
		return (free(data->pid), EXIT_FAILURE);
	execute_pipeline(data->fd_pipes, data->pid, data);
	free(data->fd_pipes);
	free(data->pid);
	data->pid = NULL;
	data->fd_pipes = NULL;
	return (EXIT_SUCCESS);
}
