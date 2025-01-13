#include "../../includes/minishell.h"

int	is_just_spaces(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg++))
			return (0);
	}
	return (1);
}

t_token	*new_token(char *start, char *end, t_type type, t_quote quote)
{
	t_token	*new;
	char	*temp;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc error");
		free(start);
		return (NULL);
	}
	else if ((start && end && end >= start) && quote)
	{
		if (quote == DQ)
		{
			temp = ft_substr(start, 0 , end - start + 1);
			if (!temp)
			{
				perror("token value malloc");
				free(new); // ajout ugo
				free(temp); // debug cas "ls |"
				free(start); // ajout ugo
				return (NULL);
			}
			new->value = ft_strdup(temp);
			//ft_concate(3, temp2, temp, temp2);
			free(temp);
		}
		else
		{
			new->value = ft_substr(start, 0 , end - start + 1);
			if (!new->value)
			{
				perror("token value malloc");
				free(new); // debug cas "ls |"
				free(start); // ajout ugo
				return (NULL);
			}
		}
	}
	else if (start && end && end >= start)
	{
		new->value = ft_substr(start, 0, end - start);
		if (!new->value)
		{
			perror("token value malloc");
			free(new);
			free(start); // ajout ugo
			return (NULL);
		}
	}
	else
		new->value = NULL;
	//free(start); // fait crash si : >
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_token_add_back(t_data *data, t_token *new)
{
	t_token	*tmp;

	if (!data->token)
	{
		new->prev = NULL;
		data->token = new;
		return ;
	}
	else
	{
		tmp = data->token;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}
