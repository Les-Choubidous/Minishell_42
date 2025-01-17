/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:58:45 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:58:47 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(int *fd_pipes, int pos, t_commands *command, t_data *data)
{
	int	exit_code;
	int	original_fd[2];

	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	if (original_fd[0] == -1 || original_fd[1] == -1)
		return (EXIT_FAILURE);
	if (dup2(fd_pipes[pos], STDIN_FILENO) == -1 || dup2(fd_pipes[pos + 3],
			STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	close_unused_fd(fd_pipes, pos, FDX_RW, pos + 1);
	exit_code = launch_builtin(data, command, data->token, STDOUT_FILENO);
	close_fd(&fd_pipes[pos]);
	close_fd(&fd_pipes[pos + 3]);
	if (dup2(original_fd[0], STDIN_FILENO) == -1 || dup2(original_fd[1],
			STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	data->exit_status = exit_code;
	return (exit_code);
}

int	execute_env(int *fd_pipes, int pos, int *pid, t_data *data)
{
	int			i;
	t_commands	*cmd;
	char		*exec_path;

	i = -1;
	cmd = data->command;
	while (cmd && ++i * 2 < pos)
		cmd = cmd->next;
	if (!cmd || !cmd->command)
		return (EXIT_FAILURE);
	exec_path = search_cmd_path(data, cmd, data->env);
	if (!exec_path)
		return (EXIT_FAILURE);
	free(exec_path);
	*pid = fork();
	if (*pid < 0)
		return (EXIT_FAILURE);
	if (*pid == 0)
	{
		if (dup2(fd_pipes[pos], STDIN_FILENO) == -1 || dup2(fd_pipes[pos + 3],
				STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		close_unused_fd(fd_pipes, pos, FDX_NONE, 2 * cmd_count(data->command));
		exit(command_executer(cmd, data));
	}
	close_fd(&fd_pipes[pos]);
	return (EXIT_FAILURE);
}

int	catch_child_execs(pid_t *pid, int num, t_data *data, int *fd_pipes)
{
	int	i;
	int	exit_code;

	i = -1;
	if (!pid || !num || !data || !fd_pipes)
		return (EXIT_FAILURE);
	while (++i < num)
	{
		if (pid[i] > 0)
		{
			waitpid(pid[i], &exit_code, 0);
			if (i == num - 1 && WIFEXITED(exit_code))
				data->exit_status = WEXITSTATUS(exit_code);
			else if (i == num - 1 && WIFSIGNALED(exit_code))
				data->exit_status = WTERMSIG(exit_code) + 128;
			else if (i == num - 1)
				data->exit_status = -1;
			close_fd(&fd_pipes[(i * 2)]);
			close_fd(&fd_pipes[(i * 2) + 3]);
		}
	}
	return (EXIT_SUCCESS);
}

int	execute_pipeline(int *fd_pipes, pid_t *pid, t_data *data)
{
	t_commands	*command;
	int			i;

	if (!fd_pipes || !pid || !data)
		return (EXIT_FAILURE);
	i = 0;
	command = data->command;
	while (command)
	{
		if (command_is_a_builtin(command))
			execute_builtin(fd_pipes, i * 2, command, data);
		else
			execute_env(fd_pipes, i * 2, &pid[i], data);
		i++;
		command = command->next;
	}
	catch_child_execs(pid, i, data, fd_pipes);
	return (EXIT_SUCCESS);
}
