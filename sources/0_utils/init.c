#include "minishell.h"

char	*init_full_path(char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			full_path = ft_strdup(env[i] + 5);
			if (!full_path)
				return (NULL);
		}
		i++;
	}
	return (full_path);
}

void	init_io(t_data *data)
{
	{
		data->input.type = INPUT;
		data->input.value = NULL;
		data->input.fd = 0;
	}
	{
		data->output.type = OUTPUT;
		data->output.value = NULL;
		data->output.fd = 1;
	}
}

int	init_data(t_data *data, char **env)
{
	ft_get_env(env, data);
	data->full_path = init_full_path(env);
	if (!data->full_path)
		return (EXIT_FAILURE);
	init_io(data);
	data->exit_status = 0;
	return (EXIT_SUCCESS);
}
