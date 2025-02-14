#include "../../includes/minishell.h"

int	perror_return(char *str)
{
	perror(str);
	return (EXIT_FAILURE);
}

int	ft_printf_exit_code(char *str, int exit_code)
{
	printf("%s", str);
	return (exit_code);
}

int	add_new_list_node(t_list **list, t_token *token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (perror_return("malloc for new list node"));
	ft_memset(new, 0, sizeof(t_list));
	new->value = ft_strdup(token->value);
	if (!new->value)
		return (perror_return("malloc for new list node value"));
	new->quote = token->quote;
	if (!*list)
		*list = new;
	else
		ft_lst_addback(*list, new);
	return (EXIT_SUCCESS);
}

void	ft_lst_addback(t_list *list, t_list *new)
{
	t_list	*ptr;

	{
		ptr = list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}
