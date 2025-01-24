/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_tokens2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:30:27 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/24 12:29:16 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_and_add_symbol_token(t_data *data, char *value, t_type type)
{
	t_token	*new;

	new = new_token(value, value + ft_strlen(value), type, NQ);
	if (!new)
		return (0);
	lst_token_add_back(data, new);
	return (1);
}

t_token	*mark_heredoc_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == HEREDOC && current->next)
		{
			if (current->next->type != ARG && current->next->type != CMD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token\n",
					2);
				ft_putstr_fd("invalid heredoc delimiter\n", 2);
				return (NULL);
			}
			current->next->type = LIM;
			if (current->next->next && current->next->next->type == ARG
				&& !current->prev)
				current->next->next->type = CMD;
		}
		current = current->next;
	}
	return (token);
}

t_token	*mark_input_tokens(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == INPUT && current->next)
		{
			if (current->next->type != ARG && current->next->type != ARG_IN_OUT && current->next->type != CMD)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
				return (NULL);
			}
			current->next->type = ARG_IN_OUT;
			if (current->next->next
				&& !current->prev)
				current->next->next->type = CMD;
		}
		current = current->next;
	}
	return (token);
}
