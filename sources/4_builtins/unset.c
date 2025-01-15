#include "minishell.h"

static void	unset_env_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->cpy_env;
	if (delete == start)
	{
		data->cpy_env = data->cpy_env->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	unset_export_node(t_env *delete, t_data *data)
{
	t_env	*start;

	start = data->export;
	if (delete == start)
	{
		data->export = data->export->next;
		free(delete->type);
		free(delete->value);
		free(delete);
		return ;
	}
	while (start->next != delete)
		start = start->next;
	start->next = start->next->next;
	free(delete->type);
	free(delete->value);
	free(delete);
}

static void	find_node_to_unset(t_env *env, t_data *data, char *value)
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

static void	find_node_to_export(t_env *env, t_data *data, char *value)
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

/******************************/

#include "minishell.h"

// Compte le nombre de variables dans ta liste chaînée
static int  env_list_size(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

// Construit la chaîne "TYPE=VALUE"
static char *join_env_var(const char *type, const char *value)
{
    char *tmp;
    char *joined;

    tmp = ft_strjoin(type, "=");       // "PATH=" par ex.
    if (!tmp)
        return (NULL);
    joined = ft_strjoin(tmp, value);   // "PATH=/bin:/usr/bin"
    free(tmp);
    return (joined);
}

// Convertit la liste chaînée data->cpy_env en tableau de char**
static char **list_to_envp(t_env *env)
{
    char    **array;
    int     size;
    int     i;

    size = env_list_size(env);
    array = malloc(sizeof(char *) * (size + 1));
    if (!array)
        return (NULL);
    i = 0;
    while (env)
    {
        array[i] = join_env_var(env->type, env->value);
        if (!array[i]) // en cas d'erreur d'allocation
        {
            // penser à free ce qui est déjà alloué
            // + free(array)
            return (NULL);
        }
        i++;
        env = env->next;
    }
    array[i] = NULL;
    return (array);
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
	 free_char_array(data->env);            // libère l'ancien tableau
    data->env = list_to_envp(data->cpy_env);	return (EXIT_SUCCESS);
}
