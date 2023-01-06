/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_setsig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 03:06:05 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:17:28 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		ft_printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
	g_lstpipe_status = 1;
}

void	handle_signal(void)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
		ft_printf("\n");
	if (signum == SIGQUIT)
		ft_printf("Quit: %d\n", SIGQUIT);
}

void	handle_child_signal(void)
{
	signal(SIGQUIT, child_handler);
	signal(SIGINT, child_handler);
}

//monmien :
// int	ms_setsig(void)
// {
// 	struct termios		termios_p;
// 	struct sigaction	act_int;
// 	struct sigaction	act_quit;

// 	if (tcgetattr(0, &termios_p) != 0)
// 		return (1);
// 	termios_p.c_lflag &= ~ECHOCTL;
// 	termios_p.c_cc[VQUIT] = 0;
// 	if (tcsetattr(0, TCSANOW, &termios_p) != 0)
// 		return (1);
// 	act_int.sa_handler = &ms_int_handler;
// 	act_int.sa_flags = SA_RESTART;
// 	sigfillset(&act_int.sa_mask);
// 	act_quit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &act_int, NULL) != 0)
// 		return (1);
// 	return (0);
// }

// void	ms_int_handler(int sign)
// {
// 	(void)sign;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }
