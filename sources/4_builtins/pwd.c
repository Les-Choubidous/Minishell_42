#include "minishell.h"

/*Il faut mettre a jour la variable pwd lorsque je change de cd */

static int	check_args(t_commands *commands)
{
	if (commands->flag)
		return (ft_printf_exit_code(PWD_ERR_FLAGS, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

char	*find_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (env[i] + key_len + 1); // Retourne la valeur après '='
		i++;
	}
	return (NULL);
}

int	builtin_pwd(t_commands *commands, t_data *data)
{
	char	*pwd;
	char	*cwd;

	if (check_args(commands))
		return (EXIT_FAILURE);

	pwd = find_env_value(data->env, "PWD");
	if (pwd)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_printf_exit_code(PWD_ERR_PWD_NOT_FOUND, EXIT_FAILURE));
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
