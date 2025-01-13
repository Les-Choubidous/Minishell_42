#include "minishell.h"

t_commands	*add_new_command_node(t_data *data)
{
	t_commands	*new;

	if (!data->command)
	{
		data->command = malloc(sizeof(t_commands));
		if (!data->command)
		{
			perror("new command node malloc");
			return (NULL);
		}
		ft_memset(data->command, 0, sizeof(t_commands));
		return (data->command);
	}
	else
	{
		new = malloc(sizeof(t_commands));
		if (!new)
		{
			perror("new command node malloc");
			return (NULL);
		}
		ft_memset(new, 0, sizeof(t_commands));
		ft_commandlst_addback(data, new);
		return (new);
	}
}

void	ft_commandlst_addback(t_data *data, t_commands *new)
{
	t_commands	*ptr;

	ptr = data->command;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
