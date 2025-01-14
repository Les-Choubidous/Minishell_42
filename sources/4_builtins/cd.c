#include "../../includes/minishell.h"

//  check sur bash
//  si tu delete le dossier parent, check le comportement de bash
//  mkdir a a/b
//  cd a/b
//  rm -rf ../a
//  pwd
//  cd ..

//  Il faut mettre a jour la variable pwd lorsque je change de cd

static int	check_args(t_commands *commands)
{
	if (commands->flag)
		return (ft_printf_exit_code(CD_ERR_FLAGS, EXIT_FAILURE));
	if (commands->arg && commands->arg->next)
		return (ft_printf_exit_code(CD_ERR_ARG, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

char	*get_target_path(t_commands *commands, t_data *data)
{
	char	*path;

	if (!commands->arg)
		path = find_env_value(data->env, "HOME");
	else if (!ft_strcmp(commands->arg->value, "-"))
	{
		path = find_env_value(data->env, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd(CD_ERR_OLDPWD, STDERR_FILENO);
			return (NULL);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = commands->arg->value;
	if (!path && !commands->arg)
		ft_putstr_fd(CD_ERR_HOME, STDERR_FILENO);
	return (path);
}

// int	overwrite_env_value(t_env *env, const char *key, const char *value)
// {
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->key, key))
// 		{
// 			free(env->value);
// 			env->value = ft_strdup(value);
// 			return (EXIT_SUCCESS);
// 		}
// 		env = env->next;
// 	}
// 	return (EXIT_FAILURE);
// }

// int	update_env_vars(char *old_pwd, char *new_pwd, t_data *data)
// {
// 	if (overwrite_env_value(data->env, "OLDPWD", old_pwd)
// 		|| overwrite_env_value(data->env, "PWD", new_pwd))
// 		return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }

/********************************************************************************** */



int	find_env_index(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, key_len) && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1); // Retourne -1 si la clé n'existe pas
}

int update_env_val(t_data *data, int i, char *key, char *value)
{
	char	*new_entry;
	char	*tmp;

	if (i < 0 || !key || !value)
		return (EXIT_FAILURE);

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (EXIT_FAILURE);

	new_entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!new_entry)
		return (EXIT_FAILURE);
	free(data->env[i]);
	data->env[i] = new_entry;

	return (EXIT_SUCCESS);
}

int	update_env_vars(char *old_pwd, char *new_pwd, t_data *data)
{
	int	old_pwd_index;
	int	new_pwd_index;

	old_pwd_index = find_env_index(data->env, "OLDPWD");
	new_pwd_index = find_env_index(data->env, "PWD");

	if (old_pwd_index >= 0 &&
		update_env_val(data, old_pwd_index, "OLDPWD", old_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (new_pwd_index >= 0 &&
		update_env_val(data, new_pwd_index, "PWD", new_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}


int	builtin_cd(t_commands *commands, t_data *data)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];
	char	*path;

	if (check_args(commands))
		return (EXIT_FAILURE);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror_return("getcwd error"));
	path = get_target_path(commands, data);
	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path) == -1)
		return (perror_return("chdir error"));
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror_return("getcwd error"));
	if (update_env_vars(old_pwd, new_pwd, data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
