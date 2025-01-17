#include "minishell.h"

/*Il faut mettre a jour la variable pwd lorsque je change de cd */

static int	check_args(t_commands *commands)
{
	if (commands->flag)
		return (ft_printf_exit_code(PWD_ERR_FLAGS, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

char	*find_env_value(t_data *data, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;

	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], key, key_len) && data->env[i][key_len] == '=')
			return (data->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_pwd(t_commands *commands, t_data *data)
{
	char	*cwd;
	
	(void)data;
	if (check_args(commands))
		return (EXIT_FAILURE);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		free(cwd);
		return (EXIT_SUCCESS);
	}
	if (!cwd)
		return (ft_printf_exit_code(PWD_ERR_PWD_NOT_FOUND, EXIT_FAILURE));
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
