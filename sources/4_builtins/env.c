#include "minishell.h"

void	write_str_fd(t_data *data, char *str_err, char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write_char_fd(data, str_err, *s++, fd);
		// if (data->err)
		// 	return ;
	}
}
void	write_char_fd(t_data *data, char *str_err, char c, int fd)
{
	if (fd > -1)
	{
		if (write(fd, &c, 1) == -1)
		{
			write_str_fd(data, str_err, str_err, 2);
			write_str_fd(data, str_err,
				": write error : no space left on device\n", 2);
			//data->err = 1;
			return ;
		}
	}
}

static void	print_env(t_data *data, int fd)
{
	t_env	*tmp;

	tmp = data->cpy_env;
	while (tmp)
	{
		write_str_fd(data, "env", tmp->type, fd);
		write_str_fd(data, "env", "=", fd);
		write_str_fd(data, "env", tmp->value, fd);
		write_str_fd(data, "env", "\n", fd);
		tmp = tmp->next;
	}
}

int	builtin_env(t_data *data, t_token *tok, int fd_out)
{
	if (tok->next)
	{
		ft_putstr_fd("INVALID_ARG_ENV\n", 2);
		data->exit_status += 1;
		return (EXIT_FAILURE);
	}
	else
	{
		print_env(data, fd_out);
		return (EXIT_SUCCESS);
	}
}

