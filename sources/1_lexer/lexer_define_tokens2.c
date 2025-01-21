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
			if (current->next->type != ARG || current->next->type != CMD)
			{
				ft_putstr_fd("minishell: syntax error:", 2);
				ft_putstr_fd(" invalid heredoc delimiter\n",2);
				// return (NULL);
			}
			current->next->type = LIM;
			// if (current->next->next && current->next->next->type == ARG)
			// 	current->next->next->type = CMD;
		}
		current = current->next;
	}
	return (token);
}

const char	*get_type_name(t_type type)
{
	switch (type)
	{
	case CMD:
		return ("CMD");
	case ARG:
		return ("ARG");
	case OUTPUT:
		return ("OUTPUT");
	case INPUT:
		return ("INPUT");
	case APPEND:
		return ("APPEND");
	case HEREDOC:
		return ("HEREDOC");
	case LIM:
		return ("LIM");
	case PIPE:
		return ("PIPE");
	case FLAG:
		return ("FLAG");
	case STDIN:
		return ("STDIN");
	case STDOUT:
		return ("STDOUT");
	case ARG_IN_OUT:
		return ("ARG_OUT");
	}
}

void	print_tokens(t_token *token)
{
	const char	*color;
	t_token		*current;
	int			token_number = 0;

	current = token;
	while (current)
	{
		if (current->type == CMD || current->type == FLAG)
			color = BLUE;
		else if (current->type == ARG || current->type == ARG_IN_OUT)
			color = ROSE;
		else if (current->type == OUTPUT || current->type == INPUT
			|| current->type == APPEND)
			color = GREEN;
		else if (current->type == PIPE)
			color = CYAN;
		else if (current->type == HEREDOC || current->type == LIM)
			color = PURPLE;
		else
			color = RESET;

		printf("\n%s========== TOKEN %d ==========%s\n", ROSE, token_number,
			RESET);
		printf("%sType        : [%s]%s\n", color, get_type_name(current->type),
			RESET);
		printf("%sValue       : [%s]%s\n", color, current->value, RESET);

		if (current->quote == 1)
			printf("%sQuote       : Simple quotes%s\n", ORANGE, RESET);
		else if (current->quote == 2)
			printf("%sQuote       : Double quotes%s\n", DARK_YELLOW, RESET);
		else
			printf("%sQuote       : None%s\n", WHITE, RESET);

		printf("%s-----------------------------%s\n", ROSE, RESET);

		// Passage au token suivant
		current = current->next;
		token_number++;
	}
}