#include "../../../includes/minishell.h"

void	failed_mess(t_data *data, char *mess, int code)
{
	ft_putstr_fd(mess, 2);
	if (*mess)
		ft_putstr_fd("\n", 2);
	//data->err = 1;
	data->exit_status += code;
}

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


