#include "minishell.h"

int	command_is_a_builtin(t_commands *node)
{
	if (!ft_strcmp(node->command, "echo")
		|| !ft_strcmp(node->command, "cd")
		|| !ft_strcmp(node->command, "pwd")
		|| !ft_strcmp(node->command, "export")
		|| !ft_strcmp(node->command, "unset")
		|| !ft_strcmp(node->command, "env")
		|| !ft_strcmp(node->command, "exit"))
		return (1);
	else
		return (0);
}

int	launch_builtin(t_commands *node, t_data *data)
{
	//int	exit_code;

	if (!ft_strcmp(node->command, "echo"))
		//exit_code = builtin_echo(node, data);
		printf("attente\n");
	printf("%s\n", data->line);
	// else if (!ft_strcmp(node->command, "cd"))
	// 	exit_code = builtin_cd(node, data);
	// else if (!ft_strcmp(node->command, "pwd"))
	// 	exit_code = builtin_pwd(node, data);
	// else if (!ft_strcmp(node->command, "export"))
	// 	exit_code = builtin_export(node, data);
	// else if (!ft_strcmp(node->command, "unset"))
	// 	exit_code = builtin_unset(node, data);
	// else if (!ft_strcmp(node->command, "env"))
	// 	exit_code = builtin_env(node, data);
	// else
	// 	exit_code = builtin_exit(node, data);
	//return (exit_code);
	return (0);
}
