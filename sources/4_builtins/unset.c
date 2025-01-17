/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:59:51 by memotyle          #+#    #+#             */
/*   Updated: 2025/01/17 18:20:22 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_node_to_unset(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_env_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

void	find_node_to_export(t_env *env, t_data *data, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, value))
		{
			unset_export_node(tmp, data);
			break ;
		}
		tmp = tmp->next;
	}
}

int	builtin_unset(t_data *data, t_token *token)
{
	t_token	*tmp_tok;

	tmp_tok = token->next;
	while (tmp_tok)
	{
		if (tmp_tok->value)
		{
			find_node_to_unset(data->cpy_env, data, tmp_tok->value);
			find_node_to_export(data->export, data, tmp_tok->value);
		}
		tmp_tok = tmp_tok->next;
	}
	data->env = list_to_envp(data->cpy_env);
	return (EXIT_SUCCESS);
}
