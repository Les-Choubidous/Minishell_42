// #include "minishell.h"

// int reverse_free_char_array(char **arr, ssize_t count, int exit_code)
// {
// 	ssize_t	i;

// 	i = 0;
// 	while (i < count)
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	return (exit_code);
// }


// int	build_new_env(t_data *data, char ***new_env, ssize_t length,
// 							ssize_t identifier_index)
// {
// 	ssize_t	i;
// 	ssize_t	j;

// 	*new_env = malloc((length) * sizeof(char *));
// 	if (!*new_env)
// 		return (EXIT_FAILURE);
// 	i = 0;
// 	j = 0;
// 	while (i < length)
// 	{
// 		if (i != identifier_index)
// 		{
// 			(*new_env)[j] = ft_strdup(data->full_env[i]);
// 			if (!(*new_env)[j])
// 				return(printf("error\n"));
// 			if (!(*new_env)[j])
// 				return (reverse_free_char_array(*new_env, j, EXIT_FAILURE)); //je n'ai pas compris
// 			j++;
// 		}
// 		i++;
// 	}
// 	(*new_env)[j] = NULL;
// 	return (EXIT_SUCCESS);
// }

// int	build_new_export(t_data *data, char ***new_env, ssize_t length,
// 							ssize_t identifier_index)
// {
// 	ssize_t	i;
// 	ssize_t	j;

// 	*new_env = malloc((length) * sizeof(char *));
// 	if (!*new_env)
// 		return (EXIT_FAILURE);
// 	i = 0;
// 	j = 0;
// 	while (i < length)
// 	{
// 		if (i != identifier_index)
// 		{
// 			(*new_env)[j] = ft_strdup(data->env_export[i]);
// 			if (!(*new_env)[j])
// 				return(printf("error\n"));
// 			if (!(*new_env)[j])
// 				return (reverse_free_char_array(*new_env, j, EXIT_FAILURE)); //je n'ai pas compris
// 			j++;
// 		}
// 		i++;
// 	}
// 	(*new_env)[j] = NULL;
// 	return (EXIT_SUCCESS);
// }


// int	builtin_unset(t_commands *c, t_data *data)
// {
// 	t_list	*ptr;

// 	if (c->flag)
// 		return (ft_printf_exit_code(UNSET_ERR_FLAGS, EXIT_FAILURE));
// 	if (!c->arg)
// 		return (EXIT_SUCCESS);
// 	ptr = c->arg;
// 	while (ptr)
// 	{
// 		if (!is_valid_name(ptr->value))
// 			printf("unset: '%s': not a valid identifier\n", ptr->value);
// 		else
// 		{
// 			if (remove_variable_from_env(ptr->value, data))
// 				return (EXIT_FAILURE);
// 			if (remove_variable_from_export(ptr->value, data))
// 				return (EXIT_FAILURE);
// 			// if (remove_from_env_lst(data, ptr))
// 			// 	return (EXIT_FAILURE);
// 		}
// 		ptr = ptr->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

// /****************DEBUG********************* */
// // int	i = 0;
// // printf(RED "full_env after unset: \n" RESET);
// // while (data->full_env[i])
// // {
// // 	printf("data->full_env[%d] : [%s]\n", i, data->full_env[i]);
// // 	i++;
// // }
// // printf(RED "env_export after unset: \n" RESET);
// // i = 0;
// // while (data->env_export[i])
// // {
// // 	printf("data->env_export[%d] : [%s]\n", i, data->env_export[i]);
// // 	i++;
// // }
// // printf(RED "LST env after unset: \n" RESET);
// // t_env	*temp = data->env;
// // while (temp)
// // {
// // 	printf("key: %s, value: %s\n", temp->key, temp->value);
// // 	temp = temp->next;
// // }
// /************************************************** */
