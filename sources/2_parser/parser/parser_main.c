/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:57:57 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:57:58 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_fd(t_data *data, t_in_out *redir, t_token *token,
		int oflag)
{
	UNUSED(data);
	if (redir->fd >= 3)
		close(redir->fd);
	if (!token->next)
		return (perror_return("Expected a value after redirection operator"));
	redir->type = token->type;
	redir->quote = token->quote;
	if (redir->value)
		free(redir->value);
	redir->value = ft_strdup(token->next->value);
	if (!redir->value)
		return (perror_return("ft_strdup for redirection value"));
	if (redir->type != HEREDOC)
	{
		redir->fd = open(redir->value, oflag, 0644);
		if (redir->fd < 0)
			return (perror_return(redir->value));
	}
	return (EXIT_SUCCESS);
}

int	parser_helper_redirections(t_data *data, t_token *token)
{
	if (token->type == INPUT || token->type == HEREDOC)
	{
		if (open_redirection_fd(data, &data->input, token, O_RDONLY))
			return (EXIT_FAILURE);
	}
	else if (token->type == OUTPUT)
	{
		if (open_redirection_fd(data, &data->output, token,
				O_WRONLY | O_TRUNC | O_CREAT))
			return (EXIT_FAILURE);
	}
	else if (token->type == APPEND)
	{
		if (open_redirection_fd(data, &data->output, token,
				O_WRONLY | O_APPEND | O_CREAT))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parser_helper_others(t_data *data, t_token *token, int *create_new_node)
{
	static t_commands	*ptr = NULL;

	if (*create_new_node)
	{
		ptr = add_new_command_node(data);
		*create_new_node = 0;
		if (!ptr)
			return (EXIT_FAILURE);
		if (!populate_node_command(ptr, token))
			return (EXIT_FAILURE);
	}
	else if (token->value[0] == '-' && token->type == FLAG)
	{
		if (populate_node_flag(ptr, token))
			return (EXIT_FAILURE);
	}
	else if (token->type == ARG)
	{
		comp_value_token(data, token);
		if (populate_node_argument(ptr, token))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	comp_value_token(t_data *data, t_token *token)
{
	if (!data || !token || !token->value)
		return (EXIT_FAILURE);
	if (data->input.value && ft_strcmp(data->input.value, token->value) == 0)
		return (EXIT_SUCCESS);
	if (data->output.value && ft_strcmp(data->output.value, token->value) == 0)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	parser(t_data *data)
{
	t_token	*ptr;
	int		create_new_node;

	ptr = data->token;
	create_new_node = 1;
	while (ptr)
	{
		if (ptr->type == PIPE)
			create_new_node = 1;
		else if (ptr->type == CMD || ptr->type == ARG || ptr->type == LIM
			|| ptr->type == FLAG)
			parser_helper_others(data, ptr, &create_new_node);
		else
			parser_helper_redirections(data, ptr);
		ptr = ptr->next;
	}
	if (create_new_node && *data->line)
		return (ft_printf_exit_code("No command after pipe\n", EXIT_FAILURE));
	if (concate_final_group_commands(data))
		return (EXIT_FAILURE);
	if (data->input.type == HEREDOC && here_doc(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
