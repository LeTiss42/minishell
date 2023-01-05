/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:19:17 by mravera           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/05 21:44:19 by trerolle         ###   ########.fr       */
=======
/*   Updated: 2023/01/05 21:46:47 by mravera          ###   ########.fr       */
>>>>>>> 08981e1ba6bc8c6907b218bb6ef66b28e99aeb1e
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
//# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
//# include <sys/types.h>
//# include <sys/stat.h>
# include <fcntl.h>
//# include <sys/wait.h>
//# include <sys/stat.h>
//# include <sys/ioctl.h>
//# include <sys/time.h>
//# include <sys/resource.h>
# include <errno.h>
# include "../Libft/libft.h"
//# include <editline/readline.h>

int	g_lstpipe_status;

//parsing command table
/*
-> char *command == commande demandee
-> char **arg == liste des arguments demandes
   |-->la fonction doit etre appelee une fois par argument
-> char *options == options demandees
*/

typedef struct s_cmd //pa
{
	char			*com;
	char			*path;
	char			**args;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				fd[2];
	struct s_redir	*redir;
	int				is_blt;
}	t_cmd;

typedef struct s_env //node
{
	char			*name;
	char			*val;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_admpipe
{
	int		**fd;
	int		*pid;
	int		nbcmd;
	int		*pipe_bltin;
}	t_admpipe;

typedef struct s_admin //ad
{
	t_env	*env;
	t_cmd	*comlist; //pa
	t_cmd	*comhd;
	char	*readline;
	int		loop;	
}	t_admin;

typedef struct s_redir
{
	char			*operator;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

//ms_main.c
int		ms_prompt(t_admin *adm);
int		ms_isbuiltin(t_admin *adm);
void	ms_bonjour(t_admin *adm);

//ms_parsing.c
int		ms_count_args(const char *s);
int		is_builtins(t_admin *adm);
int		ms_parse_line(t_admin *adm, char *str);
int		fill_cmd(t_admin *adm, char *str, int *pop);

//ms_supersplit.c
int		ms_supersplit(t_admin *adm);

//ms_utils.c
int		ms_issep(int c);
int		ms_isspace(int c);
int		ms_sizeof_word(char *str);
int		ms_free_chartab(char **tab);
int		ms_strlen_tab(char **tab);

//ms_utils_ii
char	*ms_new_pwd(char *old_pwd);
char	*ms_new_oldpwd(char *old_pwd);
int		ms_lstcomp(t_list *a, t_list *b);
int		ms_lento(char *str, char x);
char	*ft_strtrim_free(char *s1, char const *set);

//builtins
//ms_echo.c
int		ms_echo(char **str);
int		ms_pre_echo(char **str, int *opt);

//ms_pwd.c
int		ms_pwd(char **str);

//ms_cd.c
int		ms_cd(char **str, t_admin *adm);
int		ms_cd_update_env(t_list *env, char *old);

//ms_env.c
t_list	*ms_create_list_env(char **envp);
int		ms_setup_env(t_list *env);
void	ms_env(t_list *env);

//ms_envii.c
void	init(t_admin *adm, char	**env);

//ms_enviii.c
void	append_t_node(t_env **head_ref, char *name, char *val);
void	free_env(t_admin *adm);
int		count_t_node(t_env *env);
void	print_node(t_env *env, int opt);

//ms_alphaprint.c
int		ms_alphaprint(t_list *env);
t_list	*ms_biginlist(t_list *a);
t_list	*ms_smallinlst(t_list *a);
int		ms_recprint(t_list *top, t_list *env);

//ms_setvar.c
int		ms_setvar(char *var, t_list **env);
char	*ms_trimenv(char *str);
int		ms_free_noswap(char *trim, char *equal);
int		ms_swap_content(t_list *f, char *str, char *trim, char *equal);

//ms_export.c
int		ms_export(char **var, t_list **env);
int		ms_display_all(t_list *env);
int		ms_display_one(t_list *env);
int		ms_check_identifier(char *str);
char	*ms_arg_inquote(char *str);

//ms_unset.c
int		ms_unset(char **var, t_admin *adm);
int		ms_unsetone(char *var, t_admin *adm);
t_list	*ms_delone_relink(t_list *dead, t_admin *adm);

//ms_exit.c
int		ms_exit(t_admin *adm, int exit);
int		ms_exitfree(char *tofree, t_admin *adm, int exit);

//ms_free.c
void	free_all(t_admin *adm);
void	free_tab(char **tabs);
void	free_cmd(t_admin *adm);
void	free_redir(t_admin *adm);
void	free_pa(t_admin *adm);

//ms_setsig.c
void	sig_handler(int signum);
void	handle_signal(void);

//monmien :
//int		ms_setsig(void);
//void	ms_int_handler(int sign);

//ms_exec.c
int		ms_exec(t_admin	*adm);
int		ms_exec_main(t_admin *adm, t_admpipe *admpipe, int i);
void	my_exit(t_admin *adm, int flag);
void	custom_err_exit(t_admin *adm, int arg, char *str, int ret);

//ms_utils_exec.c
int		ms_get_nbcmd(t_admin *adm);
void	ms_setpipid(t_admin *adm, t_admpipe *admpipe);
int		ms_execheck(t_admin *adm);
int		fake_heredoc(t_admin *adm);
int		ms_return_error(char *str, int status, int ret);

//test
void	rl_replace_line(const char *text, int clear_undo);

//ms_lstcmd.c
t_cmd	*cmd_lstnew(t_cmd *previous);
void	cmd_lstadd_next(t_cmd **alst, t_cmd *next);
void	cmd_lst_first_or_last(t_cmd **pa, int flag);

//ms_redirection.c
void	ms_redir_lst_first_or_last(t_redir **redir, int flag);
int		ms_fill_redir(t_admin *adm, const char *l);
t_redir	*ms_redir_lstnew(struct s_redir *previous);
void	ms_redir_lstadd_next(t_redir **alst, t_redir *next);

//ms_strlen.c
int		ms_skip_between_char(const char *s, int i, char c);
int		ms_strlen_operator(const char *s);
int		ms_skip_operator(const char *s);
int		ms_strlen_separator(const char	*s, int flag);

//ms_quote.c
int		pos_n_char(char *str, int n, char c);
int		count_quote(char *str, char c);
int		check_quote(char *str, char c);
void	trim_quote(t_admin *adm);

#endif
