/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:11:32 by trerolle          #+#    #+#             */
/*   Updated: 2023/01/06 02:49:54 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	pos_n_char(char *str, int n, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			n--;
		if (n == 0)
			return (i + 1);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			return (++i);
	}
	return (i);
}

int	count_quote(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

int	check_quote(char *str, char c)
{
	if (count_quote(str, c) % 2 == 0)
	{
		return (1);
	}
	write(2, "minishell-0.5$ ", ft_strlen("minishell-0.5$" ));
	write(2, &c, 1);
	write(2, "error\n", ft_strlen("error\n"));
	write(2, "\n", 1);
	return (0);
}

void	trim_quote(t_admin *adm)
{
	int	i;

	while (adm->cmlst)
	{
		if (!adm->cmlst->com)
			break ;
		if (adm->cmlst->com[0] == '"')
			adm->cmlst->com = ft_strtrim_free(adm->cmlst->com, "\"");
		else if (adm->cmlst->com[0] == '\'')
			adm->cmlst->com = ft_strtrim_free(adm->cmlst->com, "'");
		i = -1;
		while (adm->cmlst->args[++i])
		{
			if (adm->cmlst->args[i][0] != '\'')
			{
				adm->cmlst->args[i] = ft_strtrim_free(adm->cmlst->args[i], "\"");
				check_dollar(adm, i);
			}
			else if (adm->cmlst->args[i][0] == '\'')
				adm->cmlst->args[i] = ft_strtrim_free(adm->cmlst->args[i], "'");
		}
		adm->cmlst = adm->cmlst->next;
	}
	adm->cmlst = adm->comhd;
}
