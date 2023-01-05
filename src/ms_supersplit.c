/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_supersplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:10:17 by mravera           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 18:41:19 by trerolle         ###   ########.fr       */
=======
/*   Updated: 2023/01/05 21:43:25 by mravera          ###   ########.fr       */
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e
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
