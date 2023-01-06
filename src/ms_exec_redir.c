/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravera <mravera@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 01:22:00 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 01:33:26 by mravera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../I/ft_minishell.h"

int	ms_exec_redir(t_admin *adm)
{
	if (adm->cmlst->redir)
	{
		redir_lst_fst_or_lst(&adm->cmlst->redir, 0);
		while (adm->cmlst->redir)
		{
			if (redir_outfile(adm))
				return (1);
			redir_infile(adm);
			redir_heredoc(adm);
			if (adm->cmlst->redir->next)
				adm->cmlst->redir = adm->cmlst->redir->next;
			else
				break ;
		}
	}
	return (0);
}

void	redir_heredoc(t_admin *adm)
{
	char	*tmp;
	int		fd[2];

	if (!ft_strcmp(adm->cmlst->redir->op, "<<"))
	{
		if (pipe(fd) == -1)
			my_exit(adm, write(2, "Error: pipe for <<\n", 19));
		while (1)
		{
			tmp = readline("> ");
			if (!ft_strcmp(adm->cmlst->redir->file, tmp))
				break ;
			write(fd[1], tmp, ft_strlen(tmp));
			write(fd[1], "\n", 1);
			if (tmp)
				free(tmp);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		free(tmp);
	}
}

void	redir_infile(t_admin *adm)
{
	int	infile;

	if (!ft_strcmp(adm->cmlst->redir->op, "<"))
	{
		if (!adm->cmlst->redir->file[0])
			my_exit(adm, write(2, "error : NL", 10));
		infile = open(adm->cmlst->redir->file, O_RDWR);
		if (infile == -1)
			my_exit(adm, write(2, "minishell : ", 12)
				+ write(2, adm->cmlst->redir->file,
					ft_strlen(adm->cmlst->redir->file))
				+ write(2, ": No such file or directory\n", 28));
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
}

int	redir_outfile(t_admin *adm)
{
	int	outfile;

	if (!ft_strncmp(adm->cmlst->redir->op, ">", 1))
	{
		if (!ft_strcmp(adm->cmlst->redir->op, ">>"))
			outfile = open(adm->cmlst->redir->file,
					O_RDWR | O_APPEND | O_CREAT, 0644);
		else
			outfile = open(adm->cmlst->redir->file,
					O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (outfile == -1)
		{
			if (access(adm->cmlst->redir->file, W_OK) == -1)
			{
				custom_err_redir(adm, "Permission denied", 1);
				return (1);
			}
			else
				write(2, "error : NL", 10);
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (0);
}
