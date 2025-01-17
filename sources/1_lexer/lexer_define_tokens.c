#include "../../includes/minishell.h"

t_type	get_token_type(t_data *data, char symbol, int *is_new_command)
{
	if (symbol == '|')
	{
		*is_new_command = 1;
		return (PIPE);
	}
	if (symbol == '<' && *(data->line + 1) == '<')
	{
		data->line++;
		return (HEREDOC);
	}
	if (symbol == '<')
		return (INPUT);
	if (symbol == '>')
		return (OUTPUT);
	return (-1);
}

int	create_and_add_symbol_token(t_data *data, char *value, t_type type)
{
	t_token	*new;

	new = new_token(value, value + ft_strlen(value), type, NQ);
	if (!new)
		return (0);
	lst_token_add_back(data, new);
	return (1);
}

int	add_symbol_token(t_data *data, char symbol, int *is_new_command)
{
	t_type	type;
	char	*value;

	type = get_token_type(data, symbol, is_new_command);
	if (type == HEREDOC)
	{
		if (*(data->line + 1) == '<')
		{
			printf("Syntax error: unexpected token '<<<'\n");
			data->exit_status = 2;
			return (0);
		}
		value = ft_strdup("<<");
	}
	else if (type == INPUT)
		value = ft_strdup("<");
	else if (type == OUTPUT)
		value = ft_strdup(">");
	else if (type == PIPE)
		value = ft_strdup("|");
	else
		return (0);
	if (!value)
		return (0);
	return (create_and_add_symbol_token(data, value, type));
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
