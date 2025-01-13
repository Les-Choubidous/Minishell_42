#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

/********************************MACROS***************************************/
# define SUPPORTED_SYMBOLS "<|>"
# define VALID_CHARACTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
							0123456789_"
# define FDX_NONE -1 // Aucun fd paticulier ne doit etre open
# define FDX_OR 0    // Seul entre pipe read reste ouverte
# define FDX_OW 1    // Seule la sortie pipe write reste ouvert
# define FDX_RW 2    // Les deux (entree et sortie doivent rester ouvert)

/******************************DATA_STRUCTURE**********************************/
typedef enum e_quote
{
	NQ,
	SQ,
	DQ,
}						t_quote;

typedef enum e_type
{
	CMD,
	ARG,
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
	LIM,
	PIPE,
	FLAG,
	STDIN,
	STDOUT,
	ARG_IN_OUT,
}						t_type;

typedef struct s_list
{
	char				*value;
	t_quote				quote;
	struct s_list		*next;
}						t_list;

typedef struct s_commands
{
	char				*command;
	char				**final_group;

	t_list				*flag;
	t_list				*arg;
	t_quote				command_quote;

	struct s_commands	*next;
}						t_commands;

typedef struct s_token
{
	char				*value;

	t_type				type;
	t_quote				quote;

	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_in_out
{
	int					fd;
	char				*value;
	t_type				type;
	t_quote				quote;
}						t_in_out;

typedef struct s_env
{
	char			*type;
	char			equal;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_redir
{
    int infile;
    int outfile;
    int fds_doc[2]; // pour heredoc
    int heredoc;    // boolean ou usage divers
} t_redir;

typedef struct s_pipes
{
    int     nb_pipe;      // nb de pipes détectés
    int   **fds;          // fds[i] = [read_end, write_end]
    pid_t  *pid;          // tableau d'id de processus
    int     orig_fds[2];  // copie de stdin/stdout originels
} t_pipes;

typedef struct s_data
{
	char				wich_quote_err;
	char				**env;
	//char				**env_export;
	char				*expanded_str;

	char				**path;
	char				*full_path;
	char				*line;
	int					exit_status;

	t_env				*cpy_env;
	t_env				*cpy_env2;

	t_commands			*command;
	t_token				*token;
	t_in_out			input;
	t_in_out			output;
	t_redir				*redir;
	t_pipes  *pipex;
}						t_data;

struct s_data_extended
{
    t_data   base;     // Le t_data original
    t_redir *redir;    // Pointeur vers la struct de redirection
    t_pipes *pipex;    // Pointeur vers la struct de pipes
};

int execute_single_command(t_data *data);
/********************************FUNCTIONS*************************************/
/**************************       0_utils       *******************************/
/*init_env.c*/
void					ft_get_env(char **env, t_data *data);
void					get_shlvl_env(t_data *data);
void					add_cpy_env(char *type, char *value, t_env **env, t_data *data);
t_env					*last_value(t_env *env);

/*init.c*/
int						init_data(t_data *data, char **env);
void					init_io(t_data *data);
char					*init_full_path(char **env);

/*signals.c*/
void					configure_child_signals(void);
void					configure_shell_signals(void);

/*signals_here_doc.c*/
void					signals_heredoc(void);
void					heredoc_interrupt(int signum);

/*utils.c*/
int						perror_return(char *str);
int						ft_printf_exit_code(char *str, int exit_code);
int						add_new_list_node(t_list **list, t_token *token);
void					ft_lst_addback(t_list *list, t_list *new);

/**************************       1_lexer       *******************************/
/*lexer_main.c*/
int	lexer(t_data *data, int is_new_command);
int lexer_finalize(t_data *data, t_quote current_quote,
		char **current_token, int is_new_command);
int	lexer_core(t_data *data, t_quote *current_quote,
			char **current_token, int *is_new_command);
char	*append_char(char *str, char c);
int	check_double_tokens(char *str);

/*lexer_define_tokens.c*/
t_token	*define_tokens_exit_echo(t_token *token);
t_token	*create_and_add_token(t_data *data, char *value,
		int *is_new_command);
t_token	*define_arg_type(t_token *token);
int	add_symbol_token(t_data *data, char symbol, int *is_new_command);

/*lexer_quotes.c*/
int no_quote(t_data *data, t_quote *current_quote,
		char **current_token, int *is_new_command);
int double_quote(t_data *data, t_quote *current_quote,
		char **current_token);
int single_quote(t_data *data, t_quote *current_quote,
		char **current_token);

/*lexer_utils.c*/
void	lst_token_add_back(t_data *data, t_token *new);
t_token	*new_token(char *start, char *end, t_type type, t_quote quote);
int	is_just_spaces(char *arg);


/**************************       2_parser      *******************************/
/******* Expander *******/
/*expander_main.c*/
int						expander(t_data *data);
void	failed_mess(t_data *data, char *mess, int code);
/*expander_utils.c*/

char	*ft_strjoin_char(char *str, char c);
int	is_in_single_quotes(char *str, int index);
int	is_exist_in_env(char *var, t_data *data);
size_t	get_var_len(char *str);

char	*ft_concatenate(char *before, char *in_var);
char	*extract_var(char *str, int *i);
char	*give_me_inside_var(char *var, t_data *data);
int	is_in_double_quotes(char *str, int index);

char	*expand_dollar_sequence(char **str, int *i);
char	*peer_odd_dollar(int dollar_count, char *result, char *pid_str,
		char *temp);
int	dollar_in_str(char *str, t_data *data);
int	is_finish_expand(char *str, t_data *data, int count, int *i);

/******* Heredoc ********/
// int						is_quoted_delimiter(const char *delimiter);

// void					populate_here_doc(int write_fd, char *delimiter,
// 							t_data *data);
// int						handle_here_doc_line(char *line, int fd,
// 							const char *delim, int quoted);
// int						here_doc(t_data *data);
void					populate_here_doc(int write_fd, char *delimiter,
							t_data *data);
int						here_doc(t_data *data);

/******** Parser ********/
/*parser_main.c*/
int						open_redirection_fd(t_data *data, t_in_out *redir,
							t_token *token, int oflag);
int						parser_helper_redirections(t_data *data,
							t_token *token);
int						parser_helper_others(t_data *data, t_token *token,
							int *create_new_node);
int						comp_value_token(t_data *data, t_token *token);
int						parser(t_data *data);

/*parser_command_concate.c*/
size_t					get_number_of_command_elements(t_commands *node);
int						add_cmd_to_final_group(t_commands *command_ptr,
							size_t *i);
int						add_args_to_final_group(t_commands *command_ptr,
							size_t *i);
int						add_flags_to_final_group(t_commands *command_ptr,
							size_t *i);
int						concate_final_group_commands(t_data *data);

/*parser_utils.c*/
t_commands				*add_new_command_node(t_data *data);
void					ft_commandlst_addback(t_data *data, t_commands *new);

/*parser_command_populate*/
// int						populate_command(t_data *data, t_token *token);
int						populate_node_command(t_commands *node, t_token *token);
int						populate_node_flag(t_commands *node, t_token *token);
int						populate_node_argument(t_commands *node,
							t_token *token);

/*syntaxe_line.c*/
void	syntaxe_line(char *line, t_data *data);

/**************************      3_executer     *******************************/
/*command_executer.c*/
char					**env_extract_paths(char **env);
char	*search_cmd_path(t_data *data, t_commands *cmd, char **env);
//char	*search_cmd_path(t_commands *cmd, char **env);
int						command_executer(t_commands *command, t_data *data);

// int env_split_full_path(t_data *data);
// void	print_path(char **list);

/*executer_main.c*/
int						cmd_count(t_commands *cmds);
int						executer(t_data *data);

/*fd_manager.c*/
int						close_fd(int *fd);
int						close_unused_fd(int *fd_pipes, int pos, int keep,
							int len);

/*pipeline_execute.c*/
int						execute_builtin(int *fd_pipes, int pos,
							t_commands *command, t_data *data);
int						execute_env(int *fd_pipes, int pos, int *pid,
							t_data *data);
int						catch_child_execs(pid_t *pid, int num, t_data *data,
							int *fd_pipes);
int						execute_pipeline(int *fd_pipes, pid_t *pid,
							t_data *data);
//int execute_pipeline(t_data *data);
/*pipes_builder.c*/
int						*build_pipes(int fd_out, int fd_in, int cmds_num);
//int build_pipes(int fd_out, int fd_in, int cmds_num, int **fd_pipes);

char	**env_to_tab(t_env *env);
t_token	*recup_tok_after_pipe(t_token *tmp);
void	exec_dup2_pipe(t_data *data, t_token *tmp, int i);
void	exec_dup2_simple(t_data *data);
void	ft_pipes(t_data *data);
int	pipe_in_line(t_data *data);
void	update_last_cmd(t_data *data, char *cmd_path);
char	*valid_cmd(t_data *data, char *cmd);
void	exec_cmd(t_data *data, char **env, char **cmd, t_token *tok);
void	simple_exec(t_data *data, t_token *tmp);
void	open_file(t_data *data, t_token *tok);
int executer(t_data *data);
t_token	*check_if_cmd_after_redir(t_data *data, t_token *tmp);
void	free_close_fds(t_data *data, int i);
/**************************      4_builtins     *******************************/
/*builtins_utils.c*/
int						command_is_a_builtin(t_commands *node);
int						launch_builtin(t_commands *node, t_data *data);

/*cd.c*/
char					*get_target_path(t_commands *commands, t_data *data);
// int						overwrite_env_value(t_env *env, const char *key,
// 							const char *value);
int						update_env_vars(char *old_pwd, char *new_pwd,
							t_data *data);
int						builtin_cd(t_commands *commands, t_data *data);
int	update_env_val(t_data *data, int i, char *key, char *value);
/*echo.c*/
int						builtin_echo(t_commands *commands, t_data *data);

/*env.c*/
int						builtin_env(t_commands *commands, t_data *data);

/*exit.c*/
int						builtin_exit(t_commands *command, t_data *data);

/*export.c*/
int						find_key_index(t_data *data, char *key);
int						is_valid_name(char *name);
int					export_with_arg(t_commands *command, t_data *data);
int						builtin_export(t_commands *command, t_data *data);

/*export_utils.c*/
void					just_add_to_export(t_data *data, char *key);
void					update_env_value(t_data *data, int i, char *key, char *value);
void					add_env_key(t_data *data, char *key, char *value);
void					add_env_export(t_data *data, char *key, char *value);
void					update_or_add_env(t_data *data, char *arg);

/*pwd.c*/
//char					*find_env_value(t_env *env, const char *key);
int						builtin_pwd(t_commands *commands, t_data *data);
char	*find_env_value(char **env, const char *key);
/*unset.c*/
int						reverse_free_char_array(char **arr, ssize_t count,
							int exit_code);
int						build_new_env(t_data *data, char ***new_env, ssize_t length,
							ssize_t identifier_index);
int						build_new_export(t_data *data, char ***new_env, ssize_t length,
							ssize_t identifier_index);
int						builtin_unset(t_commands *c, t_data *data);

/*unset_utils.c*/
int						remove_variable_from_export(char *identifier, t_data *data);
int						remove_variable_from_env(char *identifier, t_data *data);
int						remove_from_env_lst(t_data *data, t_list *ptr_env);

/*************************        5_free       *******************************/
/*free_mem_btw_cmd.c*/
void					free_mem_between_cmd(t_data *data);
void					free_command(t_data *data);
void					free_in_out(t_data *data);
void					free_token(t_data *data);

/*free_utils.c*/
void					free_decomposed_str(char **str1, char **str2,
							char **str3);
void					free_env_list(t_env *list);
void					free_char_array(char **array);
void					free_list(t_list *list);

/*free_all.c*/
void					free_all_memory(t_data *data);

/**************************        MAIN        ********************************/
void					exit_minishell(t_data *data, int exit_status);

/*************************        6_tests       *******************************/
/*parser tests*/
void					print_command_list(t_commands *head);
void					print_string_array(char **arr, const char *label);
void					print_list(t_list *lst, const char *label);
/*utils_test.c*/
const char				*get_type_name(t_type type);
void					print_tokens(t_token *token);

#endif
