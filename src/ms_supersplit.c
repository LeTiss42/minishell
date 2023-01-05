/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:10:17 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 16:51:34 by mravera          ###   ########.fr       */
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
