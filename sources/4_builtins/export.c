// #include "minishell.h"

// static int	check_args(t_commands *commands)
// {
// 	if (commands->flag != NULL)
// 		return (ft_printf_exit_code(EXPORT_ERR_FLAGS, EXIT_FAILURE));
// 	return (EXIT_SUCCESS);
// }

// int	find_key_index(t_data *data, char *key)
// {
// 	char	*equal;
// 	int		i;
// 	int		key_len;

// 	i = 0;
// 	while (data->full_env[i])
// 	{
// 		equal = ft_strchr(data->full_env[i], '=');
// 		if (equal)
// 		{
// 			key_len = (int)(equal - data->full_env[i]);
// 			if ((int)ft_strlen(key) == key_len && ft_strncmp(data->full_env[i],
// 					key, key_len) == 0)
// 				return (i);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

// int	is_valid_name(char *name)
// {
// 	int	i;

// 	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
// 		return (0);
// 	i = 1;
// 	while (name[i])
// 	{
// 		if (!ft_isalnum(name[i]) && name[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


// /*******************************export seul ************************** */
// // a voir si on le rajoute car cela marche MAIS
// // il faudrait juste corriger crash lie Maj de env_export
// // car full_env et export sont anormalement liees

// // static void	print_with_equal(char *str, char *equal)
// // {
// // 	*equal = '\0';
// // 	ft_putstr_fd(str, 1);
// // 	ft_putstr_fd("=\"", 1);
// // 	ft_putstr_fd(equal + 1, 1);
// // 	ft_putstr_fd("\"\n", 1);
// // 	*equal = '=';
// // }

// // static void	print_env_export(t_data *data)
// // {
// // 	char	**sorted;
// // 	char	*equal;
// // 	int		i;

// // 	sorted = sort_tab(data->env_export);
// // 	if (!sorted)
// // 		return ;
// // 	i = 0;
// // 	while (sorted[i])
// // 	{
// // 		equal = ft_strchr(sorted[i], '=');
// // 		ft_putstr_fd("declare -x ", 1);
// // 		if (equal)
// // 			print_with_equal(sorted[i], equal);
// // 		else
// // 		{
// // 			ft_putstr_fd(sorted[i], 1);
// // 			ft_putchar_fd('\n', 1);
// // 		}
// // 		i++;
// // 	}
// // 	free_char_array(sorted);
// // }
// /****************************************************************************************** */

// int	export_with_arg(__attribute__((unused)) t_commands *command,
// 		t_data *data)
// {
// 	t_list	*temp_arg;
// 	char	*arg;
// 	char	*key;
// 	char	*value;
// 	int		i;

// 	i = 0;
// 	temp_arg = command->arg;
// 	while (temp_arg)
// 	{
// 		arg = temp_arg->value;
// 		key = get_key(arg);
// 		value = get_value(arg);
// 		if (!is_valid_name(&key[i]))
// 		{
// 			printf("export : '%s': not a valid identifier\n", arg);
// 			return (EXIT_FAILURE);
// 		}
// 		i++;
// 		if (value)
// 		{
// 			update_or_add_env(data, arg);
// 			// free(value);
// 		}
// 		else
// 			just_add_to_export(data, key);
// 		// free(key);
// 		temp_arg = temp_arg->next;
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	builtin_export(t_commands *command, t_data *data)
// {
// 	// if (!command->arg)
// 	// {
// 	// 	print_env_export(data);
// 	// 	return (EXIT_SUCCESS);
// 	// }
// 	if (check_args(command) != EXIT_SUCCESS)
// 		return (EXIT_FAILURE);
// 	if (!command->arg)
// 		return (EXIT_FAILURE);
// 	else
// 		export_with_arg(command, data);
// 	return (EXIT_SUCCESS);
// }
