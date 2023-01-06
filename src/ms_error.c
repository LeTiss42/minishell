/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:50:10 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 01:30:14 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	custom_err(t_admin *adm, int arg, char *str)
{
	write(2, "minishell", 9);
	if (arg != 0)
	{
		write(2, ": ", 2);
		write(2, adm->cmlst->com, ft_strlen(adm->cmlst->com));
	}
	write(2, ": ", 2);
	write(2, adm->cmlst->args[arg], ft_strlen(adm->cmlst->args[arg]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

int	custom_err_ret(char *str, int status, int ret)
{
	g_lstpipe_status = status;
	write(2, str, ft_strlen(str));
	return (ret);
}

void	custom_err_redir(t_admin *adm, char *msg, int status)
{
	g_lstpipe_status = status;
	write(2, "minishell : ", 12);
	write(2, adm->cmlst->redir->file, ft_strlen(adm->cmlst->redir->file));
	write(2, ": ", 3);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}
