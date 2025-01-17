#include "minishell.h"

void	unset_env_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->cpy_env;
	if (delete == start)
	{
		data->cpy_env = data->cpy_env->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

void	unset_export_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->export;
	if (delete == start)
	{
		data->export = data->export->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*join_env_var(const char *type, const char *value)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(type, "=");
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, value);
	free(tmp);
	return (joined);
}

char	**list_to_envp(t_env *env)
{
	char	**array;
	int		size;
	int		i;

	size = env_list_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = join_env_var(env->type, env->value);
		if (!array[i])
		{
			free_char_array(array);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}
