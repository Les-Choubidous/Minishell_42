// #include "minishell.h"

// void	just_add_to_export(t_data *data, char *key)
// {
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	while (data->env_export[i])
// 		i++;
// 	temp = ft_strjoin(key, "=");
// 	data->env_export[i] = ft_strdup(temp);
// 	free(temp);
// 	data->env_export[i] = NULL;
// }

// void	update_env_value(t_data *data, int i, char *key, char *value)
// {
// 	char	*key_eq;
// 	char	*tmp;

// 	key_eq = ft_strjoin(key, "=");
// 	free(data->full_env[i]);
// 	if (value)
// 	{
// 		tmp = ft_strjoin(key_eq, value);
// 		free(key_eq);
// 	}
// 	else
// 	{
// 		tmp = key_eq;
// 	}
// 	free(data->env_export[i]);
// 	data->full_env[i] = tmp;
// 	data->env_export[i] = ft_strdup(tmp);
// }

// void	add_env_key(t_data *data, char *key, char *value)
// {
// 	char	*tmp;
// 	int		len;

// 	len = 0;
// 	while (data->full_env[len])
// 		len++;
// 	data->full_env = (char **)ft_realloc((void **)data->full_env,
// 				(size_t)(len + 1), (size_t)(len + 2));
// 	data->env_export = (char **)ft_realloc((void **)data->env_export,
// 				(size_t)(len + 1), (size_t)(len + 2));
// 	tmp = join_key_val(key, value);
// 	data->full_env[len] = tmp;
// 	data->env_export[len] = ft_strdup(tmp);
// 	data->full_env[len + 1] = NULL;
// 	data->env_export[len + 1] = NULL;
// 	//free_env_list(data->env);
// 	//data->env = ft_get_env(data->full_env);
// }

// void	add_env_export(t_data *data, char *key, char *value)
// {
// 	int		i;
// 	char	*temp;
// 	char	*joined;

// 	i = 0;
// 	while (data->env_export[i])
// 		i++;
// 	temp = ft_strjoin(key, "=");
// 	if (value)
// 	{
// 		joined = ft_strjoin(temp, value);
// 		free(temp);
// 		temp = joined;
// 	}
// 	data->full_env[i] = ft_strdup(temp);
// 	data->env_export[i] = ft_strdup(temp);
// 	free(temp);
// 	data->full_env[i + 1] = NULL;
// 	data->env_export[i + 1] = NULL;
// 	//free_env_list(data->env);
// 	//data->env = ft_get_env(data->full_env);
// }

// void	update_or_add_env(t_data *data, char *arg)
// {
// 	char	*key;
// 	char	*value;
// 	int		index;

// 	key = get_key(arg);
// 	index = find_key_index(data, key);
// 	value = get_value(arg);
// 	if (index >= 0)
// 		update_env_value(data, index, key, value);
// 	else
// 		add_env_key(data, key, value);
// 	free(key);
// 	if (value)
// 		free(value);
// }
