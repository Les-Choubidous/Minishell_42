/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:31 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 18:14:29 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*sort_list(t_env *cpy, int (*cmp)(const char *, const char *))
{
	t_env	*tmp;
	char	*temp;
	char	*temp2;

	tmp = cpy;
	while (cpy && cpy->next)
	{
		if (cmp(cpy->type, cpy->next->type) > 0)
		{
			temp = cpy->type;
			temp2 = cpy->value;
			cpy->type = cpy->next->type;
			cpy->value = cpy->next->value;
			cpy->next->type = temp;
			cpy->next->value = temp2;
			cpy = tmp;
		}
		else
			cpy = cpy->next;
	}
	return (tmp);
}

static int	event_expansion(t_data *data)
{
	t_token	*tmp;
	int		i;
	char	*error_mess;

	error_mess = NULL;
	tmp = data->token->next;
	while (tmp)
	{
		i = 0;
		while (tmp->value[i])
		{
			if (tmp->value[i] == '!' && tmp->value[i + 1])
			{
				ft_putstr_fd("minishell: ", 2);
				error_mess = ft_substr(tmp->value, i, ft_strlen(tmp->value));
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

static void	update_env_from_tokens(t_data *data, t_token *token)
{
	t_token	*tmp;
	int		exist;

	tmp = data->token->next;
	while (token)
	{
		if (event_expansion(data))
			return ;
		if (!is_valid_name(export_key(tmp->value)))
		{
			tmp = token->next;
			token = token->next;
			continue ;
		}
		tmp = token->next;
		if (token->value)
			exist = find_if_env_exist(data->cpy_env, token->value);
		if (exist != -1)
			modif_env_node(data, token->value, exist);
		else
			add_env_node(data, token->value);
		modif_export(data, token->value);
		token = token->next;
	}
}

static void	display_export_order(t_data *data, int fd)
{
	t_env	*sort_tmp;

	sort_tmp = data->export;
	while (sort_tmp)
	{
		putstr_fd(data, "export", "declare -x ", fd);
		putstr_fd(data, "export", sort_tmp->type, fd);
		if (sort_tmp->equal)
			putstr_fd(data, "export", "=\"", fd);
		if (sort_tmp->value)
			putstr_fd(data, "export", sort_tmp->value, fd);
		if (sort_tmp->equal)
			putstr_fd(data, "export", "\"", fd);
		putstr_fd(data, "export", "\n", fd);
		sort_tmp = sort_tmp->next;
	}
}

int	builtin_export(t_data *data, t_token *token, int fd)
{
	t_token	*tmp_tok;

	tmp_tok = token->next;
	if (tmp_tok && !ft_strcmp(tmp_tok->value, "|"))
	{
		tmp_tok = tmp_tok->next;
		if (!ft_strcmp(tmp_tok->value, "export"))
			tmp_tok = tmp_tok->next;
	}
	if (!data->export)
	{
		get_env_for_export(data->env, data);
		data->export = sort_list(data->export, ft_strcmp);
	}
	if (!tmp_tok || tmp_tok->type != ARG)
	{
		display_export_order(data, fd);
		return (EXIT_FAILURE);
	}
	if (tmp_tok->value[0] == '\0')
	{
		ft_putstr_fd(EXPORT_ERR_IDENTIFIER, 2);
		return (EXIT_FAILURE);
	}
	if (!data->nb_pipe)
		update_env_from_tokens(data, tmp_tok);
	return (EXIT_SUCCESS);
}
