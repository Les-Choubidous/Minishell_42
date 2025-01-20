/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_define_tokens2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:30:27 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/20 16:47:13 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
