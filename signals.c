#include "includes/parse.h"

void	sig_int_handler(int s)
{
	(void)s;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
}

void	set_default(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}