/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:01:58 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 11:53:36 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	init(t_admin *adm, char	**env)
{
	size_t	i;
	size_t	j;
	char	*name;
	char	*val;

	i = ms_strlen_tab(env);
	adm->env = NULL;
	j = 0;
	while (j < i)
	{
		name = ft_substr(env[j], 0, ms_lento(env[j], '='));
		val = ft_strdup(env[j] + 1 + ms_lento(env[j], '='));
		append_t_node(&adm->env, name, val);
		j++;
	}
	adm->cmlst = NULL;
	g_lstpipe_status = 0;
}

int	ms_env(t_admin *adm)
{
	if (adm->cmlst->args[1])
	{
		if (access(adm->cmlst->args[1], X_OK))
		{
			g_lstpipe_status = errno;
			perror(adm->cmlst->com);
		}
		else
		{
			g_lstpipe_status = errno;
			perror(adm->cmlst->com);
		}
	}
	else
	{
		g_lstpipe_status = 0;
		print_node(adm->env, 'c');
	}
	return (0);
}

int	get_i_env(t_admin *adm, char *name)
{
	t_env	*temp;
	int		i;

	temp = adm->env;
	i = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (i);
		temp = temp->next;
		i++;
	}
	return (-1);
}

t_env	*get_env(t_admin *adm, int i)
{
	t_env	*temp;

	temp = adm->env;
	while (i--)
		temp = temp->next;
	return (temp);
}

void	add_env(t_admin *adm, int argid, char *name, char *val)
{
	t_env	*temp;
	int		i;

	if (!name)
		name = ft_substr(adm->cmlst->args[argid], 0,
				ms_lento(adm->cmlst->args[argid], '='));
	if (!val)
		val = ft_strtrim(adm->cmlst->args[argid]
				+ ms_lento(adm->cmlst->args[argid],
					'=') + 1, "\"");
	i = get_i_env(adm, name);
	if (i == -1)
		append_t_node(&adm->env, name, val);
	else
	{
		temp = get_env(adm, i);
		temp->val = val;
	}
	g_lstpipe_status = 0;
}
