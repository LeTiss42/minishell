/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:46:12 by mravera           #+#    #+#             */
/*   Updated: 2023/01/05 17:30:03 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_parse_line(t_admin *adm, char *str)
{
	char	*tmp;
	int		pop;

	adm->comlist = pa_lstnew(NULL);
	adm->comhd = adm->comlist;
	tmp = str;
	pop = 0;
	while (*str)
	{
		str += populate_pa(adm, str, &pop);
		if (pop < 0)
			return (1);
		if (*str == '|')
		{
			++str;
			while (ft_isspace(*str) && *str)
				++str;
			pa_lstadd_next(&adm->comlist, pa_lstnew(adm->comlist));
		}
	}
	free(tmp);
	return (0);
}

int	populate_pa(t_admin *adm, char *str, int *pop)
{
	int	n;
	int	ret;

	n = 0;
	ret = populate_redir(adm, str);
	if (ret < 0)
	{
		*pop = -1;
		write(2, "Error : pop_redir\n", 18);
		return (-1);
	}
	adm->comlist->com = ft_strtrim_f(ft_substr(str + ret, 0,
				ft_strlen_sp(str + ret, 0)), " ");
	if (is_builtins(adm))
		adm->comlist->is_blt = 1;
	if (ft_count_args(str) == -1)
	{
		*pop = -1;
		return (-1);
	}
	adm->comlist->args = malloc(sizeof(char *) * (ft_count_args(str) + 1));
	while ((*(str + ret) != '|' && *(str + ret)))
		check_special_char(adm, str, &ret, &n);
	adm->comlist->args[n] = NULL;
	return (ret);
}
