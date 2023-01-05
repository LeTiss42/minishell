/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:45:14 by trerolle          #+#    #+#             */
/*   Updated: 2023/01/05 19:49:20 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	ms_redir_lst_first_or_last(t_redir **redir, int flag)
{
	if (flag == 0)
	{
		while (*redir)
		{
			if ((*redir)->prev == NULL)
				break ;
			*redir = (*redir)->prev;
		}
	}
	else
	{
		while (*redir)
		{
			if ((*redir)->next == NULL)
				break ;
			*redir = (*redir)->next;
		}
	}
}

void    ms_redir_lstadd_next(t_redir **alst, t_redir *next)
{
	if (*alst)
	{
		ms_redir_lst_first_or_last(alst, 1);
		(*alst)->next = next;
		ms_redir_lst_first_or_last(alst, 1);
	}
	else
		*alst = next;
}

t_redir	*ms_redir_lstnew(struct s_redir *previous)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->operator = NULL;
	redir->file = NULL;
	if (previous)
        redir->prev = previous;
	else
		redir->prev = NULL;
	redir->next = NULL;
	return (redir);
}

int	ms_fill_redir(t_admin *adm, const char *l)
{
	int	ret;

	ret = 0;
	while (*(l + ret) == ' ')
		ret++;
	while (*(l + ret) == '>' || *(l + ret) == '<')
	{
		if (!adm->comlist->redir)
			adm->comlist->redir = ms_redir_lstnew(NULL);
		else
			ms_redir_lstadd_next(&adm->comlist->redir, ms_redir_lstnew(adm->comlist->redir));
		adm->comlist->redir->operator = ft_strtrim_f(
				ft_substr(l + ret, 0, ms_strlen_operator(l + ret)), " ");
		ret += ms_strlen_operator(l + ret);
		adm->comlist->redir->file = ft_strtrim_f(
				ft_substr(l + ret, 0, ms_strlen_separator(l + ret, 0)), " ");
		ret += ms_strlen_separator(l + ret, 0);
	}
	return (ret);
}