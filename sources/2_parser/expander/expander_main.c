#include "../../../includes/minishell.h"

char	*expand_exit_status(t_data *data, int *i)
{
	char	*before;
	char	*in_var;

	before = ft_strdup(data->expanded_str);
	if (!before)
		return (failed_mess(data, "malloc failed", 1), NULL);
	in_var = ft_itoa(data->exit_status);
	if (!in_var)
		return (free(before), failed_mess(data, "malloc failed", 1), NULL);
	(*i) += 2;
	free(data->expanded_str);
	data->expanded_str = ft_concatenate(before, in_var);
	free(before);
	free(in_var);
	if (!data->expanded_str)
		return (failed_mess(data, "malloc failed", 1), NULL);
	return (data->expanded_str);
}

char	*expand_stuff(t_data *data, char *str, char *var, int *i)
{
	char	*before;
	char	*in_var;

	before = ft_strdup(data->expanded_str);
	if (!before)
		return (failed_mess(data, "malloc failed", 1), NULL);
	if (is_exist_in_env(var, data))
		in_var = give_me_inside_var(var, data);
	else
		in_var = expand_dollar_sequence(&str, i);
	free(data->expanded_str);
	data->expanded_str = ft_concatenate(before, in_var);
	free(before);
	free(in_var);
	if (!data->expanded_str)
		return (failed_mess(data, "malloc failed", 1), NULL);
	return (data->expanded_str);
}

char	*expand_else(t_data *data, char *str, int *i)
{
	char	*tmp;

	tmp = ft_strdup(data->expanded_str);
	if (!tmp)
		return (failed_mess(data, "malloc failed", 1), NULL);
	free(data->expanded_str);
	data->expanded_str = ft_strjoin_char(tmp, str[*i]);
	free(tmp);
	if (!data->expanded_str)
		return (failed_mess(data, "malloc failed", 1), NULL);
	(*i)++;
	return (data->expanded_str);
}

char	*expan_var(char *str, t_data *data)
{
	int		i;
	char	*var;

	i = 0;
	data->expanded_str = ft_strdup("");
	if (!data->expanded_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?' && !is_in_single_quotes(str, i))
		{
			data->expanded_str = expand_exit_status(data, &i);
			if (!data->expanded_str)
				return (NULL);
		}
		else if (str[i] == '$' && !is_in_single_quotes(str, i))
		{
			var = extract_var(str + i, &i);
			if (!var)
				return (failed_mess(data, "Failed to extract variable", 1), NULL);
			data->expanded_str = expand_stuff(data, str, var, &i);
			free(var);
			if (!data->expanded_str)
				return (NULL);
		}
		else
		{
			data->expanded_str = expand_else(data, str, &i);
			if (!data->expanded_str)
				return (NULL);
		}
	}
	return (data->expanded_str);
}

int	expander(t_data *data)
{
	if (!data->line)
		return (EXIT_FAILURE);
	data->expanded_str = NULL;
	if (dollar_in_str(data->line, data))
	{
		data->expanded_str = expan_var(data->line, data);
		if (!data->expanded_str)
			return (EXIT_FAILURE);
		free(data->line);
		data->line = ft_strdup(data->expanded_str);
		if (!data->line)
		{
			free(data->expanded_str);
			data->expanded_str = NULL;
			return (EXIT_FAILURE);
		}
		free(data->expanded_str);
		data->expanded_str = NULL;
	}
	return (EXIT_SUCCESS);
}
