#include "minishell.h"
#include <sys/stat.h>

//ajout ugo
static int is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	**env_extract_paths(char **env)
{
	char	**path_split;
	char	**path_split_full;
	int		i;

	i = 0;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (!env[i] || !(ft_strchr(env[i], '=') + 1))
		return (NULL);
	path_split = ft_split(ft_strchr(env[i], '=') + 1, ':');
	i = 0;
	while (path_split[i])
		i++;
	path_split_full = (char **)malloc((i + 1) * sizeof(char *));
	if (path_split_full)
	{
		path_split_full[i] = 0;
		while (--i >= 0)
			path_split_full[i] = ft_strjoin(path_split[i], "/");
	}
	free_char_array(path_split);
	return (path_split_full);
}

// char	*search_cmd_path(t_commands *cmd, char **env)
// {
// 	char	**paths;
// 	char	*exec_path;
// 	int		i;

// 	if (!cmd || !env)
// 		return (0);
// 	i = -1;
// 	paths = env_extract_paths(env);
// 	while (paths && paths[++i])
// 	{
// 		exec_path = ft_strjoin(paths[i], cmd->command);
// 		if (!exec_path)
// 			return (NULL);
// 		if (access(exec_path, X_OK | F_OK) == 0)
// 			return (free_char_array(paths), exec_path);
// 		free(exec_path);
// 		exec_path = NULL;
// 	}
// 	if (!exec_path)
// 		exec_path = cmd->command;
// 	free_char_array(paths);
// 	if (access(exec_path, X_OK | F_OK) == 0)
// 		return (exec_path);
// 	return (ft_putstr_fd(CMD_NOT_FOUND, 2), ft_putendl_fd(cmd->command, 2), NULL);
// }

//new version ugo
char	*search_cmd_path(t_data *data, t_commands *cmd, char **env)
{
	char	**paths;
	char	*exec_path;
	int		i;

	if (!cmd || !env || !cmd->command[0])
		return (NULL);
	if (is_directory(cmd->command))
		return (data->exit_status = 126, ft_putstr_fd(cmd->command, 2),
			ft_putstr_fd(": is a directory", 2), NULL);//putendl??
	i = -1;
	paths = env_extract_paths(env);
	while (paths && paths[++i])
	{
		exec_path = ft_strjoin(paths[i], cmd->command);
		if (!exec_path)
			return (NULL);
		if (access(exec_path, X_OK | F_OK) == 0)
			return (free_char_array(paths), exec_path);
		free(exec_path);
		exec_path = NULL;
	}
	if (!exec_path)
		exec_path = ft_strdup(cmd->command);
	free_char_array(paths);
	if (access(exec_path, X_OK | F_OK) == 0)
		return (exec_path);
	return (data->exit_status = 127, ft_putstr_fd(CMD_NOT_FOUND, 2),
		ft_putendl_fd(cmd->command, 2), free(exec_path), NULL);
}

// int	command_executer(t_commands *command, t_data *data)
// {
// 	char	*exec_path;

// 	if (!command || !command->command)
// 		return (EXIT_FAILURE);
// 	exec_path = 0;
// 	if (access(command->command, X_OK | F_OK) == 0)
// 		data->exit_status = execve(command->command, command->final_group,
// 				data->full_env);
// 	else
// 		exec_path = search_cmd_path(command, data->full_env);
// 	if (exec_path)
// 		data->exit_status = execve(exec_path, command->final_group,
// 				data->full_env);
// 	else
// 	{
// 		data->exit_status = 127;
// 		free(exec_path);
// 	}
// 	free(exec_path);
// 	exit(data->exit_status);
// }

// new version ugo
int	command_executer(t_commands *command, t_data *data)
{
	char	*exec_path;

	if (!command || !command->command)
		return (EXIT_FAILURE);
	exec_path = NULL;
		exec_path = search_cmd_path(data, command, data->env);
	if (exec_path)
		data->exit_status = execve(exec_path, command->final_group,
				data->env);
	free(exec_path);
	exit(data->exit_status);
}
