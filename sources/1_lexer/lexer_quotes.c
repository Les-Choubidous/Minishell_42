#include "../../includes/minishell.h"

t_token	*create_and_add_token(t_data *data, char *value,
		int *is_new_command)
{
	t_type	type;
	t_token	*new;

	type = ARG;
	if (*is_new_command)
	{
		type = CMD;
		*is_new_command = 0;
	}
	new = new_token(value, value + ft_strlen(value), type, NQ);
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	return (new);
}

int single_quote(t_data *data, t_quote *current_quote,
		char **current_token)
{
	if (*data->line == '\'')
		*current_quote = NQ;
	else
	{
		*current_token = append_char(*current_token, *data->line);
		if (!*current_token)
			return (0);
	}
	return (1);
}

int double_quote(t_data *data, t_quote *current_quote,
		char **current_token)
{
	if (*data->line == '\"')
		*current_quote = NQ;
	else
	{
		*current_token = append_char(*current_token, *data->line);
		if (!*current_token)
			return (0);
	}
	return (1);
}

int no_quote(t_data *data, t_quote *current_quote,
		char **current_token, int *is_new_command)
{
	if (*data->line == '\'')
		*current_quote = SQ;
	else if (*data->line == '\"')
		*current_quote = DQ;
	else if (ft_isspace((unsigned char)*data->line))
	{
		if (*current_token && **current_token)
		{
			if (!create_and_add_token(data, *current_token, is_new_command))
				return (0);
			*current_token = NULL;
		}
	}
	else if (ft_strchr(SUPPORTED_SYMBOLS, *data->line)
		&& *data->line != '\'' && *data->line != '\"')
	{
		if (*current_token && **current_token)
		{
			if (!create_and_add_token(data, *current_token, is_new_command))
				return (0);
			*current_token = NULL;
		}
		if (!add_symbol_token(data, *data->line, is_new_command))
			return (0);
	}
	else
		*current_token = append_char(*current_token, *data->line);
	return (1);
}
