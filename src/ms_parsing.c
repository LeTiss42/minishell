/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:46:12 by mravera           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 21:29:54 by trerolle         ###   ########.fr       */
=======
/*   Updated: 2023/01/05 21:46:50 by mravera          ###   ########.fr       */
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	is_builtins(t_admin *adm)
{
	if (!adm->comlist->com)
		return (1);
	adm->comlist->com = ft_strtolower(adm->comlist->com);
	if (!ft_strcmp("echo", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("cd", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("pwd", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("env", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("export", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("unset", adm->comlist->com))
		return (1);
	else if (!ft_strcmp("exit", adm->comlist->com))
		return (1);
	return (0);
}

void	check_special_char(t_admin *adm, char *line, int *ret, int *n)
{
	while (*(line + (*ret)) == ' ')
		(*ret)++;
	if (*(line + *ret))
	{
		if (*(line + *ret) == '\'')
		{
			adm->comlist->args[*n] = ft_substr(line + *ret, 0,
					pos_n_char(line + *ret, 2, '\''));
			*ret += pos_n_char(line + *ret, 2, '\'');
		}
		else if (*(line + *ret) == '"')
		{
			adm->comlist->args[*n] = ft_substr(line + *ret, 0,
					pos_n_char(line + *ret, 2, '"'));
			*ret += pos_n_char(line + *ret, 2, '"');
		}
		else
		{
			adm->comlist->args[*n] = ft_strtrim_f(ft_substr(line + *ret, 0,
						ms_strlen_separator(line + *ret, 0)), " ");
			*ret += ms_strlen_separator(line + *ret, 0);
		}
	}
	*n = *n + 1;
	*ret += ms_fill_redir(adm, line + (*ret));
}


int	ms_count_args(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] && s[i] != '|')
	{
		i = skip_between_char(s, i, '\'');
		if (i == -1)
			return (-1);
		i = skip_between_char(s, i, '"');
		if (i == -1)
			return (-1);
		if (!ft_isspace(s[i]) && s[i] != '>' && s[i] != '<'
			&& (ft_isspace(s[i + 1]) || s[i + 1] == '\0'
				|| s[i + 1] == '>' || s[i + 1] == '<' || s[i + 1] == '|'))
			++count;
		if (s[i] == '>' || s[i] == '<')
			i += ft_skip_op(s + i);
		else
			++i;
	}
	return (count);
}

int	ms_parse_line(t_admin *adm, char *str)
{
	char	*tmp;
	int		pop;

	adm->comlist = cmd_lstnew(NULL);
	adm->comhd = adm->comlist;
	tmp = str;
	pop = 0;
	while (*str)
	{
		str += fill_cmd(adm, str, &pop);
		if (pop < 0)
			return (1);
		if (*str == '|')
		{
			++str;
			while (ft_isspace(*str) && *str)
				++str;
			cmd_lstadd_next(&adm->comlist, cmd_lstnew(adm->comlist));
		}
	}
	free(tmp);
	return (0);
}

int	fill_cmd(t_admin *adm, char *str, int *pop)
{
	int	n;
	int	ret;

	n = 0;
	ret = ms_fill_redir(adm, str);
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
