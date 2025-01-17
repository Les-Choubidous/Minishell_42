#include "../includes/minishell.h"

void	exit_minishell(t_data *data, int exit_status);
void	launch_minishell(t_data *data);
static volatile sig_atomic_t	g_signal_received = 0;

static int	is_line_empty_or_need_continue(t_data *data)
{
	int	i;

	i = 0;
	if (!data->line[0])
		return (free(data->line), 1);
	while (ft_isspace(data->line[i]))
	{
		i++;
	}
	if (data->line[i] == '\0')
		return (free(data->line), 69);
	if (data->line[0] == ':' && !data->line[1])
		return (free(data->line), 69);
	if (data->line[0] == '!' && !data->line[1])
	{
		data->exit_status = 1;
		return (free(data->line), 69);
	}
	return (0);
}

void	launch_minishell(t_data *data)
{
	while (1)
	{
		data->line = readline(PROMPTE);
		if (data->line == NULL)
			exit_minishell(data, EXIT_SUCCESS);
		if (is_line_empty_or_need_continue(data))
			continue ;
		if (g_signal_received)
		{
			data->exit_status = 130;
			free(data->line);
			continue ;
		}
		syntaxe_line(data->line, data);
		if (ft_strlen(data->line))
			add_history(data->line);
		if (expander(data) == EXIT_FAILURE || lexer(data, 1) == EXIT_FAILURE
			|| parser(data) == EXIT_FAILURE || executer(data) == EXIT_FAILURE)
		{
			free_mem_between_cmd(data);
			continue ;
		}
		free_mem_between_cmd(data);
	}
}

void	exit_minishell(t_data *data, int exit_status)
{
	if (data->pid)
		free(data->pid);
	data->pid = NULL;
	ft_printf_colour(RED, "Exiting minishell 👋\n");
	free_all_memory(data);
	clear_history();
	exit(exit_status);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	configure_shell_signals();
	if (init_data(&data, env) == EXIT_FAILURE)
		exit_minishell(&data, EXIT_FAILURE);
	launch_minishell(&data);
	return (EXIT_SUCCESS);
}
