// #include "minishell.h"




// int	remove_variable_from_export(char *identifier, t_data *data)
// {
// 	size_t	length;
// 	ssize_t	identifier_index;
// 	char	**new_env;

// 	length = 0;
// 	identifier_index = -1;
// 	new_env = NULL;
// 	while (data->env_export[length])
// 	{
// 		if (!ft_strncmp(identifier, data->env_export[length], ft_strlen(identifier))
// 			&& data->env_export[length][ft_strlen(identifier)] == '=')
// 			identifier_index = length;
// 		length++;
// 	}
// 	if (identifier_index == -1)
// 		return (EXIT_SUCCESS);
// 	if (build_new_export(data, &new_env, length, identifier_index))
// 		return (EXIT_FAILURE);
// 	//free_char_array(data->env_export);
// 	data->env_export = new_env;
// 	return (EXIT_SUCCESS);
// }

// int	remove_variable_from_env(char *identifier, t_data *data)
// {
// 	size_t	length;
// 	ssize_t	identifier_index;
// 	char	**new_env;

// 	length = 0;
// 	identifier_index = -1;
// 	new_env = NULL;
// 	while (data->full_env[length])
// 	{
// 		if (!ft_strncmp(identifier, data->full_env[length], ft_strlen(identifier))
// 			&& data->full_env[length][ft_strlen(identifier)] == '=')
// 			identifier_index = length;
// 		length++;
// 	}
// 	if (identifier_index == -1)
// 		return (EXIT_SUCCESS);
// 	if (build_new_env(data, &new_env, length, identifier_index))
// 		return (EXIT_FAILURE);
// 	//free_char_array(data->full_env);
// 	data->full_env = new_env;
// 	return (EXIT_SUCCESS);
// }

// // int	remove_from_env_lst(t_data *data, t_list *ptr_env)
// // {
// // 	t_env	*temp;
// // 	t_env	*prev;

// // 	temp = data->env;
// // 	prev = NULL;
// // 	while (temp)
// // 	{
// // 		if (!ft_strcmp(temp->key, ptr_env->value))
// // 		{
// // 			if (prev)
// // 				prev->next = temp->next;
// // 			else
// // 				data->env = temp->next;
// // 			free(temp->key);
// // 			free(temp->value);
// // 			free(temp);
// // 			return (EXIT_SUCCESS);
// // 		}
// // 		prev = temp;
// // 		temp = temp->next;
// // 	}
// // 	return (EXIT_FAILURE);
// // }
