#include "minishell.h"


//exclamation mark
static int	point_dexclamation(t_data *data)
{
	t_token	*tmp;
	int		i;
	char *error_mess;

	error_mess = NULL;
	tmp = data->token->next;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '!' && tmp->value[i + 1])
			{
				ft_putstr_fd("minishell: " , 2);
				error_mess = ft_substr(tmp->value, i , ft_strlen(tmp->value));
				ft_putstr_fd(error_mess, 2);
				ft_putstr_fd(": event not found\n", 2);
				free(error_mess);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	handle_while(t_data *data, t_token *tmp_tok)
{
	t_token	*tmp_tiktok;
	int		exist;

	tmp_tiktok = data->token->next;
	while (tmp_tok)
	{
		if (point_dexclamation(data))
			return ;
		if (!is_valid_name(export_key(tmp_tiktok->value)))
		{
			tmp_tiktok = tmp_tok->next;
			tmp_tok = tmp_tok->next;
			continue ;
		}
		tmp_tiktok = tmp_tok->next;
		if (tmp_tok->value)
			exist = find_if_env_exist(data->cpy_env, tmp_tok->value);
		if (exist != -1)
			modif_env_node(data, tmp_tok->value, exist);
		else
			add_env_node(data, tmp_tok->value);
		modif_export(data, tmp_tok->value);
		tmp_tok = tmp_tok->next;
	}
}
static void	display_export_order(t_data *data, int fd)
{
	t_env	*sort_tmp;

	sort_tmp = data->cpy_env2;
	while (sort_tmp)
	{
		write_str_fd(data, "export", "declare -x ", fd);
		write_str_fd(data, "export", sort_tmp->type, fd);
		if (sort_tmp->equal)
			write_str_fd(data, "export", "=\"", fd);
		if (sort_tmp->value)
			write_str_fd(data, "export", sort_tmp->value, fd);
		if (sort_tmp->equal)
			write_str_fd(data, "export", "\"", fd);
		write_str_fd(data, "export", "\n", fd);
		sort_tmp = sort_tmp->next;
	}
}


int	builtin_export(t_data *data, t_token *token, int fd)
{
	t_token	*tmp_tok;

	tmp_tok = token->next;
	if (!data->cpy_env2)
	{
		get_env2(data->env, data);
		data->cpy_env2 = sort_list(data->cpy_env2, ft_strcmp);
	}
	if (!tmp_tok)
	{
		display_export_order(data, fd);
		return (EXIT_FAILURE);
	}
	if (tmp_tok->value[0] == '\0')
	{
		ft_putstr_fd("INVALID_VAL_EXPORT", 2);
		return (EXIT_FAILURE);
	}
	handle_while(data, tmp_tok);
	return (EXIT_SUCCESS);
}

