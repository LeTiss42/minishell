/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:53:44 by mravera           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 18:45:00 by trerolle         ###   ########.fr       */
=======
/*   Updated: 2023/01/05 18:51:47 by mravera          ###   ########.fr       */
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

t_cmd	*cmd_lstnew(t_cmd *previous)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->com = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
	if (previous)
		cmd->prev = previous;
	else
		cmd->prev = NULL;
	cmd->redir = NULL;
	cmd->is_blt = 0;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_lstadd_next(t_cmd **alst, t_cmd *next)
{
	if (*alst)
	{
		cmd_lst_first_or_last(alst, 1);
		(*alst)->next = next;
		cmd_lst_first_or_last(alst, 1);
	}
	else
		*alst = next;
}

void	cmd_lst_first_or_last(t_cmd **pa, int flag)
{
	if (flag == 0)
	{
		while (*pa)
		{
			if ((*pa)->prev == NULL)
				break ;
			*pa = (*pa)->prev;
		}
	}
	else
	{
		while (*pa)
		{
			if ((*pa)->next == NULL)
				break ;
			*pa = (*pa)->next;
		}
	}
}
