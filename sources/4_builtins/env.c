// #include "minishell.h"

// static int	check_args(t_commands *commands)
// {
// 	if (commands->arg)
// 		return (ft_printf_exit_code(ENV_ERR_ARG, EXIT_FAILURE));
// 	if (commands->flag)
// 		return (ft_printf_exit_code(ENV_ERR_FLAGS, EXIT_FAILURE));
// 	return (EXIT_SUCCESS);
// }

// int	builtin_env(t_commands *command, t_data *data)
// {
// 	size_t	i;

// 	if (!data->full_env) //!data->env && )
// 		return (EXIT_SUCCESS);
// 	if (check_args(command))
// 		return (EXIT_FAILURE);
// 	i = 0;
// 	while (data->full_env[i])
// 		ft_printf("%s\n", data->full_env[i++]);
// 	return (EXIT_SUCCESS);
// }
