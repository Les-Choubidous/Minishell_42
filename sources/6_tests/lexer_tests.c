#include "../../includes/minishell.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by user42            #+#    #+#             */
/*   Updated: 2025/01/13 00:00:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
			// Si tu veux l'appeler autrement :
			return ("ARG_OUT");
		default:
			// Par sécurité, couvrir le cas où un type n'est pas géré
			return ("UNKNOWN");
	}
}

void	print_tokens(t_token *token)
{
	const char	*color;
	//t_token		*current;
	int			token_number = 0;

	//current = token;
	while (token)
	{
		if (token->type == CMD || token->type == FLAG)
			color = BLUE;
		else if (token->type == ARG || token->type == ARG_IN_OUT)
			color = ROSE;
		else if (token->type == OUTPUT || token->type == INPUT
			|| token->type == APPEND)
			color = GREEN;
		else if (token->type == PIPE)
			color = CYAN;
		else if (token->type == HEREDOC || token->type == LIM)
			color = PURPLE;
		else
			color = RESET;

		printf("token_number = %d\n", token_number);
		printf("\n%s========== TOKEN %d ==========%s\n", GREEN, token_number,
			RESET);
		printf("%sType        : [%s]%s\n", color, get_type_name(token->type),
			RESET);
		printf("%sValue       : [%s]%s\n", color, token->value, RESET);

		printf("%s-----------------------------%s\n", ROSE, RESET);

		token = token->next;
		token_number++;
	}
}
