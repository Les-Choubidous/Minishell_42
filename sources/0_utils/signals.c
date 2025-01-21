/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:50 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 18:02:10 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

static void	sigint_shell_action(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_redisplay();
	rl_on_new_line();
}

void	configure_shell_signals(void)
{
	signal(SIGINT, sigint_shell_action);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

static void	sigint_child_action(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
}

void	configure_child_signals(void)
{
	signal(SIGINT, sigint_child_action);
	signal(SIGQUIT, SIG_DFL);
}
