/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:10:17 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 10:36:18 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_supersplit(t_admin *adm)
{
	char	*temp;

	if (!adm->readline)
		return (1);
	temp = ft_strtrim(adm->readline, "\f\n\r\t\v ");
	if (ms_parse_line(adm, temp))
	{
		free(temp);
		return (3);
	}
	trim_quote(adm);
	return (0);
}

char	*ft_strjoin_f(char *s1, char *s2, int mode)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = ft_calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	if (mode == 1)
		free(s1);
	else if (mode == 2)
		free(s2);
	else if (mode == 3)
	{
		free(s1);
		free(s2);
	}
	return (res);
}
