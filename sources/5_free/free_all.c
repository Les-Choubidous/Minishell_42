#include "minishell.h"

void	free_all_memory(t_data *data)
{
	if (!data)
		return ;
	// free_char_array(data->full_env);
	// free_char_array(data->env_export);
	free_char_array(data->path);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->full_path)
	{
		free(data->full_path);
		data->full_path = NULL;
	}
	free_env_list(data->cpy_env);
	free_env_list(data->export);
	free_token(data);
	free_command(data);
	free_in_out(data);
}
