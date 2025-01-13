#include "../../includes/minishell.h"

int	add_symbol_token(t_data *data, char symbol, int *is_new_command)
{
	t_type	type;
	t_token	*new;

	type = ARG;
	if (symbol == '|')
	{
		type = PIPE;
		*is_new_command = 1;
	}
	else if (symbol == '<')
		type = INPUT;
	else if (symbol == '>')
		type = OUTPUT;
	new = new_token((char *)&symbol, (char *)&symbol + 1, type, NQ);
	if (!new)
		return (0);
	lst_token_add_back(data, new);
	return (1);
}

t_token	*define_arg_type(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current)
	{
		if (current->type == OUTPUT || current->type == INPUT
			|| current->type == APPEND)
		{
			if (current->next && current->next->type == ARG)
				current->next->type = ARG_IN_OUT;
		}
		current = current->next;
	}
	return (token);
}

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

t_token	*define_tokens_exit_echo(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token;
	while (current)
	{
		if (current->type == CMD)
		{
			if (ft_strcmp(current->value, "exit") == 0
				|| ft_strcmp(current->value, "echo") == 0)
			{
				while (current->next && (current->next->type == FLAG
						|| current->next->type == ARG))
				{
					if (current->next && (current->next->type == FLAG))
						current->next->type = ARG;
					current = current->next;
				}
			}
		}
		current = current->next;
	}
	return (token);
}
