// // #include "minishell.h"

// // static int	check_valid_flag(char *str)
// // {
// // 	int	i;

// // 	i = 1;
// // 	if (str[0] != '-' || str[1] != 'n')
// // 		return (1);
// // 	while (str[i] == 'n')
// // 		i++;
// // 	if (str[i] != '\0')
// // 		return (1);
// // 	return (0);
// // }

// // static void	print_echo(char	**array, int flag, int pos)
// // {
// // 	int	first;

// // 	first = 1;
// // 	while (array[pos])
// // 	{
// // 		if (first)
// // 		{
// // 			printf("%s", array[pos]);
// // 			pos++;
// // 			first = 0;
// // 		}
// // 		if (array[pos])
// // 			printf(" %s", array[pos++]);
// // 	}
// // 	if (!flag)
// // 		printf("\n");
// // }

// // int	builtin_echo(t_commands *commands, __attribute__((unused)) t_data *data)
// // {
// // 	int		pos;
// // 	int		flag;

// // 	flag = 0;
// // 	pos = 1;
// // 	while (commands->final_group[pos])
// // 	{
// // 		if (!check_valid_flag(commands->final_group[pos]))
// // 		{
// // 			flag = 1;
// // 			pos++;
// // 		}
// // 		else
// // 			break ;
// // 	}
// // 	print_echo(commands->final_group, flag, pos);
// // 	return (EXIT_SUCCESS);
// // }

// #include "minishell.h"

// static int	check_valid_flag(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (str[0] != '-' || str[1] != 'n')
// 		return (1);
// 	while (str[i] == 'n')
// 		i++;
// 	if (str[i] != '\0')
// 		return (1);
// 	return (0);
// }

// static void	print_echo(char **array, int flag, int pos)
// {
// 	int	first;

// 	first = 1;
// 	while (array[pos])
// 	{
// 		// Ignore les arguments vides (comme ceux générés par des variables non définies)
// 		if (ft_strlen(array[pos]) == 0)
// 		{
// 			pos++;
// 			continue;
// 		}
// 		// Gestion du premier argument (sans espace avant)
// 		if (first)
// 		{
// 			printf("%s", array[pos]);
// 			first = 0;
// 		}
// 		else
// 		{
// 			printf(" %s", array[pos]);
// 		}
// 		pos++;
// 	}
// 	if (!flag)
// 		printf("\n");
// }

// int	builtin_echo(t_commands *commands, __attribute__((unused)) t_data *data)
// {
// 	int		pos;
// 	int		flag;

// 	flag = 0;
// 	pos = 1;
// 	// Vérifie et traite les flags
// 	while (commands->final_group[pos])
// 	{
// 		if (!check_valid_flag(commands->final_group[pos]))
// 		{
// 			flag = 1;
// 			pos++;
// 		}
// 		else
// 			break;
// 	}
// 	// Imprime les arguments en ignorant les chaînes vides
// 	print_echo(commands->final_group, flag, pos);
// 	return (EXIT_SUCCESS);
// }
