/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:56:50 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/22 12:03:38 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include <readline/history.h>
// #include <readline/readline.h>
// #include <signal.h>
// #include <unistd.h>

// int	sig_event(void)
// {
// 	return (EXIT_SUCCESS);
// }

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	g_waiting = 1;
// 	rl_done = 1;
// }

// void	ft_signal(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	rl_event_hook = sig_event;
// 	sa.sa_handler = handle_sigint;
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGTSTP, SIG_IGN);
// }

// void	set_parent_exec_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGSTOP, SIG_IGN);
// }

// void	set_child_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGSTOP, SIG_IGN);
// }

#include "minishell.h"

static void    handle_sigint(int signum)
{
    (void)signum;
    write(2, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_waiting = 1;
}

void    signal_handlers(void)
{
    g_waiting = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void    reset_signal_handler(t_data *data)
{
    if ((g_waiting == 1 || g_waiting == 3)
        && data->exit_status == 130)
    {
        g_waiting = 0;
        data->exit_status = 0;
    }
    if (g_waiting == 4 && data->exit_status == 131)
    {
        g_waiting = 0;
        data->exit_status = 0;
    }
}