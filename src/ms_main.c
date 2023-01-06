/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:21:55 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 13:10:11 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	main(int ac, char **av, char **env)
{
	t_admin	adm;
	int		temp;

	ms_bonjour();
	init(&adm, env);
	while (1)
	{
		handle_signal();
		if (!ms_prompt(&adm))
			break ;
		temp = ms_supersplit(&adm);
		if (temp == 1)
			break ;
		if (temp == 2 || temp == 3)
			continue ;
		if (ms_exec(&adm))
			break ;
		free_cmd(&adm);
		free(adm.readline);
	}
	free_env(&adm);
	free(adm.readline);
	(void)ac;
	(void)av;
	return (0);
}

int	ms_prompt(t_admin *adm)
{
	struct termios	saved;
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	adm->readline = readline("minishell-0.5$ ");
	if (adm->readline && *adm->readline)
		add_history(adm->readline);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	if (!adm->readline)
		return (0);
	return (1);
}

int	ms_isbuiltin(t_admin *adm)
{
	if (!adm->cmlst->com)
		return (1);
	adm->cmlst->com = ft_strtolower(adm->cmlst->com);
	if (!ft_strcmp("echo", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("cd", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("pwd", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("env", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("export", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("unset", adm->cmlst->com))
		return (1);
	else if (!ft_strcmp("exit", adm->cmlst->com))
		return (1);
	return (0);
}

void	ms_bonjour(void)
{
	printf("\nYou are using our lite version of bash called Minishell.");
	printf("\nTo update your account to use zsh, please don't run \n");
	printf("'chsh -s /bin/zsh' as it will not do anything at all.\n");
	printf("For more details, please don't visit https://support.apple.com\n");
	printf("as it has nothing to do with us.\n\n");
	return ;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_admin			adm;
// 	struct termios	termios_s;

// 	(void)argc;
// 	(void)argv;
// 	if (tcgetattr(0, &termios_s) != 0)
// 		return (1);
// 	adm.env = ms_create_list_env(envp);
// 	ms_setsig();
// 	ms_bonjour(&adm);
// 	ms_prompt(&adm);
// 	if (tcsetattr(0, TCSANOW, &termios_s) != 0)
// 		return (1);
// 	return (0);
// }

// int	ms_prompt(t_admin *adm)
// {
// 	char	*buffer;

// 	buffer = NULL;
// 	while (adm->loop == 1)
// 	{
// 		if (buffer != NULL)
// 		{
// 			free(buffer);
// 			buffer = NULL;
// 		}
// 		buffer = readline("minishell-0.5$ ");
// 		if (buffer && *buffer)
// 			add_history(buffer);
// 		if (!buffer || (ms_builtin(buffer, adm) == 0))
// 			return (ms_exitfree(buffer, adm, 1));
// 	}
// 	free(buffer);
// 	return (1);
// }
