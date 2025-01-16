#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

// Fonction pour gérer SIGINT dans le shell (processus parent)
static void	sigint_shell_action(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

// Fonction pour configurer la gestion des signaux pour le shell
void	configure_shell_signals(void)
{
	signal(SIGINT, sigint_shell_action);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// Fonction pour gérer SIGINT dans les processus enfants
static void	sigint_child_action(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
}

// Fonction pour configurer la gestion des signaux pour les processus enfants
void	configure_child_signals(void)
{
	signal(SIGINT, sigint_child_action);
	signal(SIGQUIT, SIG_DFL);
}
