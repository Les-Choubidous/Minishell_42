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

int	check_syntax_export(char *value, t_data *data)
{
	int	i;
	int	digit;

	(void)data; // Pour éviter le warning de paramètre non utilisé

	i = 0;
	digit = 0;
	while (value[i])
	{
		if (ft_isdigit((unsigned char)value[i]))
			digit++;
		i++;
		if (value[i - 1] == '=')
			break ;
	}
	if (digit == i || !ft_strcmp(value, "="))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	if (value[i - 1] == '=')
		return (i);
	return (0);
}


void	no_equal_in_export(t_data *data, char *value)
{
	t_env	*tmp;

	add_cpy_env2(ft_substr(value, 0, ft_strlen(value)), ft_strdup(""),
		&data->cpy_env2, data);
	tmp = data->cpy_env2;
	while (tmp->next)
		tmp = tmp->next;
	tmp->equal = '\0';
}

void	modif_export_node(t_data *data, char *value, int exist)
{
	int		i;
	t_env	*tmp;

	i = check_syntax_export(value, data);
	tmp = data->cpy_env2;
	while (exist > 0)
	{
		tmp = tmp->next;
		exist--;
	}
	free(tmp->value);
	tmp->value = ft_substr(value, i, ft_strlen(value));
	tmp->equal = '=';
}

void	modif_export(t_data *data, char *value)
{
	int		exist;
	int		i;
	char	*sub;

	i = check_syntax_export(value, data);
	if (i == -1)
		return (ft_putstr_fd("minishell: export: `", 2), ft_putstr_fd(value, 2),
			ft_putstr_fd("': not a valid identifier\n", 2));
	sub = ft_strjoin(value, "=");
	exist = find_if_env_exist(data->cpy_env2, sub);
	free(sub);
	if (exist != -1 && i)
		modif_export_node(data, value, exist);
	else if (exist == -1 && i)
		add_cpy_env2(ft_substr(value, 0, i - 1), ft_substr(value, i,
				ft_strlen(value)), &data->cpy_env2, data);
	else if (exist == -1 && !i)
		no_equal_in_export(data, value);
	data->cpy_env2 = sort_list(data->cpy_env2, ft_strcmp);
}
