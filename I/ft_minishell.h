/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <trerolle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:19:17 by mravera           #+#    #+#             */
/*   Updated: 2023/01/06 14:02:20 by trerolle         ###   ########.fr       */
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

typedef struct s_admin
{
	t_env	*env;
	t_cmd	*cmlst;
	t_cmd	*comhd;
	char	*readline;
	int		loop;	
}	t_admin;

typedef struct s_redir
{
	char			*op;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}	t_redir;

//ms_main.c
int		ms_prompt(t_admin *adm);
int		ms_isbuiltin(t_admin *adm);
void	ms_bonjour(void);

//ms_parsing.c
void	check_special_char(t_admin *adm, char *line, int *ret, int *n);
int		ms_count_args(const char *s);
int		ms_parse_line(t_admin *adm, char *str);
int		ms_fill_cmd(t_admin *adm, char *str, int *pop);

//ms_supersplit.c
int		ms_supersplit(t_admin *adm);
char	*ft_strjoin_f(char *s1, char *s2, int mode);

//ms_split_redir_utils.c
void	redir_lst_fst_or_lst(t_redir **redir, int flag);
void	redir_lstadd_next(t_redir **alst, t_redir *next);
t_redir	*redir_lstnew(struct s_redir *previous);

//ms_utils.c
int		ms_issep(int c);
int		ms_isspace(int c);
int		ms_sizeof_word(char *str);
int		ms_free_chartab(char **tab);
int		ms_strlen_tab(char **tab);

//ms_utils_ii.c
char	*ms_new_pwd(char *old_pwd);
char	*ms_new_oldpwd(char *old_pwd);
int		ms_lstcomp(t_list *a, t_list *b);
int		ms_lento(char *str, char x);
char	*ft_strtrim_free(char *s1, char const *set);

//ms_utilsiii.c
int		ft_strcmp(char *s1, char *s2);
char	*ft_strtolower(char *str);
char	*ft_strsubreplace(const char *s, const char *set, const char *sub);
int		result_len(const char *s, const char *set, int *cnt);

//builtins
//ms_echo.c
int		ms_echo(char **str);
int		ms_pre_echo(char **str, int *opt);

//ms_pwd.c
int		ms_pwd(void);

//ms_cd.c
int		ms_cd(t_admin *adm);
//int		ms_cd_update_env(t_list *env, char *old);

//ms_env.c
void	init(t_admin *adm, char	**env);
int		ms_env(t_admin *adm);
int		get_i_env(t_admin *adm, char *name);
t_env	*get_env(t_admin *adm, int i);
void	add_env(t_admin *adm, int argid, char *name, char *val);

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
int		ms_export(t_admin *adm);
int		ft_isexport(const char *str);
void	show_export(t_admin *adm);
void	add_export(t_admin *adm, int i);
void	sort_export(t_admin *adm, int count);

//ms_unset.c
int		ms_unset(t_admin *adm);
int		ms_isunset(const char *str);
void	delete_t_node(t_env **head_ref, t_env *del);

//ms_exit.c
void	ft_exit(t_admin *adm);
void	exit_no_arg(t_admin *adm);

//ms_error.c
void	custom_err(t_admin *adm, int arg, char *str);
int		custom_err_ret(char *str, int status, int ret);
void	custom_err_redir(t_admin *adm, char *msg, int status);

//ms_free.c
void	free_all(t_admin *adm);
void	free_tab(char **tabs);
void	free_com(t_admin *adm);
void	free_redir(t_admin *adm);
void	free_cmd(t_admin *adm);

//ms_setsig.c
void	sig_handler(int signum);
void	handle_signal(void);
void	child_handler(int signum);
void	handle_child_signal(void);

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

//ms_exec_check_execve.
int		ms_exec_check_execve(t_admin *adm);
char	**get_env2d(t_env *env);
int		create_cmd(char **path, char **cmd);

//ms_exec_builtins.c
int		exec_blt(t_admin *adm);
int		ms_exec_builtins(t_admin *adm, t_admpipe *admpipe, int i);

//ms_exec_redir.c
int		ms_exec_redir(t_admin *adm);
void	redir_heredoc(t_admin *adm);
void	redir_infile(t_admin *adm);
int		redir_outfile(t_admin *adm);

//ms_close_pipes.c
void	free_pipe(t_admin *adm, t_admpipe *admpipe);
void	my_close(t_admin *adm, t_admpipe *admpipe, int n);
void	my_close2(int **fd, int n_pa, int n, int flag);
void	wait_pipe(t_admin *adm, t_admpipe *admpipe);

//test
void	rl_replace_line(const char *text, int clear_undo);

//ms_lstcmd.c
t_cmd	*cmd_lstnew(t_cmd *previous);
void	cmd_lstadd_next(t_cmd **alst, t_cmd *next);
void	cmd_lst_first_or_last(t_cmd **cmlst, int flag);

//ms_redirection.c
void	ms_redir_lst_first_or_last(t_redir **redir, int flag);
int		ms_fill_redir(t_admin *adm, const char *l);
t_redir	*ms_redir_lstnew(struct s_redir *previous);
void	ms_redir_lstadd_next(t_redir **alst, t_redir *next);

//ms_strlen_utils.c
int		ms_skip_between_char(const char *s, int i, char c);
int		ms_strlen_operator(const char *s);
int		ms_skip_operator(const char *s);
int		ms_strlen_separator(const char	*s, int flag);

//ms_quote.c
int		pos_n_char(char *str, int n, char c);
int		count_quote(char *str, char c);
int		check_quote(char *str, char c);
void	trim_quote(t_admin *adm);

//ms_check_dollar.c
void	check_dollar(t_admin *adm, int n);
void	check_after_dollar(t_admin *adm, int i, int j);
char	*edit_status_exit(t_admin *adm, int i);

#endif
