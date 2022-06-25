#include <minishell.h>

char	*sig_error_2(int sig)
{
	if (sig == 25)
		return ("File size limit exceeded (core dumped)");
	else if (sig == 26)
		return ("Virtual timer expired");
	else if (sig == 27)
		return ("Profiling timer expired");
	else if (sig == 29)
		return ("I/O possible");
	else if (sig == 30)
		return ("Power failure");
	else if (sig == 31)
		return ("Bad system call (core dumped)");
	else
		return ("Signal unknown");
}

char	*sig_error_1(int sig)
{	
	if (sig == 11)
		return ("Segmentation fault (core dumped)");
	else if (sig == 12)
		return ("User defined signal 2");
	else if (sig == 14)
		return ("Alarm clock");
	else if (sig == 15)
		return ("Terminated");
	else if (sig == 16)
		return ("Stack fault");
	else if (sig == 19)
		return ("Stopped(SIGSTOP)");
	else if (sig == 20)
		return ("Stopped(SIGTSTP)");
	else if (sig == 21)
		return ("Stopped(SIGTTIN)");
	else if (sig == 22)
		return ("Stopped(SIGTTOU)");
	else if (sig == 24)
		return ("CPU time limit exceeded (core dumped)");
	else
		return (sig_error_2(sig));
}

char	*sig_error(int sig)
{
	if (sig == 1)
		return ("Hangup");
	else if (sig == 2)
		return ("");
	else if (sig == 3)
		return ("Quit (core dumped)");
	else if (sig == 4)
		return ("Illegal instruction (core dumped)");
	else if (sig == 5)
		return ("Trace/breakpoint trap (core dumped)");
	else if (sig == 6)
		return ("Aborted (core dumped)");
	else if (sig == 7)
		return ("Bus error (core dumped)");
	else if (sig == 8)
		return ("Floating point exception (core dumped)");
	else if (sig == 9)
		return ("Killed");
	else if (sig == 10)
		return ("User defined signal 1");
	else
		return (sig_error_1(sig));
}
