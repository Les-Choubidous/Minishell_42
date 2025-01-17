/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:43 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 17:56:46 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_heredoc(void)
{
	signal(SIGINT, heredoc_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_interrupt(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}
