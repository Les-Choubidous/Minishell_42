#include "minishell.h"

int	populate_node_command(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	node->command = ft_strdup(token->value);
	if (!node->command)
		return (EXIT_FAILURE);
	node->command_quote = token->quote;
	return (EXIT_SUCCESS);
}

int	populate_node_flag(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	if (add_new_list_node(&node->flag, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	populate_node_argument(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	if (add_new_list_node(&node->arg, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
