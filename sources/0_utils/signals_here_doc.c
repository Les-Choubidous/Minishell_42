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
