#include "includes/parse.h"
//normal shell 
void	sig_int_handler(int s)
{
	(void)s;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void	set_signals(t_envi	*dup_env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
	set_exit_status(1,&dup_env);
}

//in prrocess
void	sig_quit_handler(int s)
{
	(void)s;
	ft_putstr_fd("Quit : 3\n",1);
}
void	set_child_process(void)
{
	signal(SIGQUIT,sig_quit_handler);
}
//heredoc
static void handler_heredoc(int sig)
{

    (void)sig;
   g_heredoc_interrupted = 6;
   ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
void	set_herdoc(void)
{
	signal(SIGINT, handler_heredoc);
}
