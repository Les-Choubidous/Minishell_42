#include "minishell.h"

/*utils*/
size_t	get_var_len(char *str)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	i++;
	if (!str)
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}

int	is_exist_in_env(char *var, t_data *data)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, var) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_in_single_quotes(char *str, int index)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && i < index)
	{
		if (!str[i])
			return (in_single);
		if (str[i] == '\"' && !in_double)
			in_double = 1;
		else if (str[i] == '\"' && in_double)
			in_double = 0;
		if (str[i] == '\'' && !in_double && !in_single)
			in_single = 1;
		else if (str[i] == '\'' && !in_double && in_single)
			in_single = 0;
		i++;
	}
	return (in_single);
}

char	*ft_strjoin_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
	{
		new_str = malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}

	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

/*utils2*/
int	is_in_double_quotes(char *str, int index)
{
	int	in_double;
	int	i;

	in_double = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && i < index)
	{
		if (!str[i])
			return (in_double);
		if (str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			in_double = !in_double;
		i++;
	}
	return (in_double);
}

char	*give_me_inside_var(char *var, t_data *data)
{
	char	*in_var;
	t_env	*tmp;

	in_var = NULL;
	tmp = data->cpy_env;
	printf("1\n");
	while (tmp)
	{
		if (ft_strcmp(tmp->value, var) == 0)
		{
			in_var = ft_strdup(tmp->value);
			printf("in var : %s\n", in_var);
			if (!in_var)
				return (failed_mess(data, "malloc failed", 1), NULL);
			return (in_var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*extract_var(char *str, int *i)
{
	char	*var;
	size_t	var_len;

	if (!str)
		return (NULL);
	var_len = 0;
	var = NULL;
	var_len = get_var_len(str);
	if (!var_len)
		return (NULL);
	(*i)++;
	var = ft_substr(str, 1, var_len);
	if (!var)
		return (NULL);
	(*i) += var_len;
	return (var);
}

char	*ft_concatenate(char *before, char *in_var)
{
	char	*result;
	size_t	total_len;

	total_len = ft_strlen(before) + ft_strlen(in_var);
	result = malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	ft_strcpy(result, before);
	ft_strcat(result, in_var);
	return (result);
}

/*dollars*/

int	is_finish_expand(char *str, t_data *data, int count, int *i)
{
	char	*var;

	var = extract_var(str + *i, i);
	if (var && (is_exist_in_env(var, data) || (str + *i)[0] != '?'))
	{
		free(var);
		return (1);
	}
	if (var)
	{
		free(var);
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	dollar_in_str(char *str, t_data *data)
{
	int	i;
	int	open;
	int	count;

	i = 0;
	open = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		if (str[i] == '\'' && !open)
			open = 1;
		else if (str[i] == '\'' && open)
			open = 0;
		else if (str[i] == '$')
		{
			if (is_finish_expand(str, data, count, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*peer_odd_dollar(int dollar_count, char *result, char *pid_str,
		char *temp)
{
	while (dollar_count >= 2)
	{
		if (!result)
			result = ft_strdup(pid_str);
		else
		{
			temp = ft_strjoin(result, pid_str);
			free(result);
			result = temp;
		}
		dollar_count -= 2;
	}
	if (dollar_count == 1)
	{
		if (!result)
			result = ft_strdup("$");
		else
		{
			temp = ft_strjoin(result, "$");
			free(result);
			result = temp;
		}
	}
	return (result);
}

char	*expand_dollar_sequence(char **str, int *i)
{
	size_t	dollar_count;
	char	*pid_str;
	char	*result;
	char	*temp;

	temp = NULL;
	dollar_count = 0;
	pid_str = "(pid)";
	result = NULL;
	while ((*str)[*i] == '$')
	{
		dollar_count++;
		(*i)++;
	}
	result = peer_odd_dollar(dollar_count, result, pid_str, temp);
	return (result);
}
