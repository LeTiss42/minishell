/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:00:54 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 17:09:25 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_export(t_admin *adm)
{
	int	i;
	int	checker;
	int	status;

	status = 0;
	if (!adm->cmlst->args[1])
		show_export(adm);
	else
	{
		i = 0;
		while (adm->cmlst->args[++i])
		{
			checker = ft_isexport(adm->cmlst->args[i]);
			if (checker)
				add_export(adm, i);
			else
			{
				status = 1;
				custom_err(adm, i, "Not a valid identifier");
			}
		}
	}
	g_lstpipe_status = status;
	return (0);
}

int	ft_isexport(const char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
		return (0);
	while (str[++i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| str[i] == '=' || str[i] == '_' || str[i] == ':' || str[i] == '/'
			|| str[i] == '.' || str[i] == '"')
			continue ;
		return (0);
	}
	return (1);
}

void	show_export(t_admin *adm)
{
	t_admin	dup;
	t_env	*tmp;

	dup.env = NULL;
	tmp = adm->env;
	while (tmp)
	{
		add_env(&dup, 1, ft_strdup(tmp->name), ft_strdup(tmp->val));
		tmp = tmp->next;
	}
	sort_export(&dup, count_t_node(dup.env));
	print_node(dup.env, 1);
	free_env(&dup);
}

void	add_export(t_admin *adm, int i)
{
	if (ft_strchr(adm->cmlst->args[i], '='))
	{
		if (ft_strlen(ft_strchr(adm->cmlst->args[i], '=')) > 1)
			add_env(adm, i, NULL, NULL);
		else
			add_env(adm, i, NULL, ft_strdup(""));
	}
	else
		add_env(adm, i, NULL, ft_strdup("NULL"));
}

void	sort_export(t_admin *adm, int count)
{
	t_env	*tmp;
	int		i;
	int		j;
	char	*buf;

	i = 0;
	while (i++ < count)
	{
		j = 0 + i;
		tmp = adm->env;
		while (j++ < count)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				buf = tmp->val;
				tmp->val = tmp->next->val;
				tmp->next->val = buf;
				buf = tmp->name;
				tmp->name = tmp->next->name;
				tmp->next->name = buf;
			}
			tmp = tmp->next;
		}
	}
}
