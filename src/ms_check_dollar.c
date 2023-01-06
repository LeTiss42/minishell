/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 02:39:17 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 02:55:57 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

void	check_dollar(t_admin *adm, int n)
{
	int		i;

	i = -1;
	while (adm->cmlst->args[n][++i])
	{
		check_after_dollar(adm, n, i);
	}
}

void	check_after_dollar(t_admin *adm, int i, int j)
{
	char	*env;
	char	*tmp;
	char	*tmp2;

	if (adm->cmlst->args[i][j] == '$')
	{
		if (adm->cmlst->args[i][j + 1] == '?')
			adm->cmlst->args[i] = edit_status_exit(adm, i);
		env = ft_substr(adm->cmlst->args[i], j + 1,
				ms_lento(adm->cmlst->args[i] + j + 1, ' '));
		env = ft_strtrim_free(env, "'");
		if (get_i_env(adm, env) != -1)
		{
			tmp = adm->cmlst->args[i];
			tmp2 = ft_strjoin("$", get_env(adm, get_i_env(adm, env))->name);
			adm->cmlst->args[i] = ft_strsubreplace(adm->cmlst->args[i], tmp2,
					get_env(adm, get_i_env(adm, env))->val);
			free(tmp);
			free(tmp2);
		}
		free(env);
	}
}

char	*edit_status_exit(t_admin *adm, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	tmp = adm->cmlst->args[i];
	tmp2 = ft_itoa(g_lstpipe_status);
	ret = ft_strsubreplace(adm->cmlst->args[i], "$?", tmp2);
	free(tmp);
	free(tmp2);
	return (ret);
}
