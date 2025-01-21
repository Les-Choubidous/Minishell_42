/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_tokens2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:30:27 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/21 15:00:09 by memotyle         ###   ########.fr       */
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
			if (current->next->type != ARG)
			{
				ft_putstr_fd("minishell: syntax error:\
								invalid heredoc delimiter\n", 2);
				return (NULL);
			}
			current->next->type = LIM;
		}
		current = current->next;
	}
	return (token);
}
