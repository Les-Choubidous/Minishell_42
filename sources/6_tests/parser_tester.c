#include "../../includes/minishell.h"

/*
void	print_list(t_list *lst, const char *label)
{
	printf("%s\n", label);
	if (!lst) {
		printf(GREY "  (empty)\n" RESET);
		return ;
	}
	while (lst) {
		printf("  %s\n", lst->value);
		lst = lst->next;
	}
}

void	print_string_array(char **arr, const char *label)
{
	printf("%s\n", label);
	if (!arr) {
		printf(GREY "  (empty)\n" RESET);
		return ;
	}
	for (int i = 0; arr[i]; i++) {
		printf("  {%s}\n", arr[i]);
	}
}

void	print_command_list(t_commands *head)
{
	t_commands	*current;
	int			i;

	current = head;
	i = 0;
	while (current) {
		printf(ORANGE "====== COMMAND NODE %d =======\n" RESET, i++);
		if (current->command)
		{
			printf(BLUE "Command :\n" RESET);
		printf("  %s\n", current->command);
		}
		else
		{
			printf(GREY "Command :\n" RESET);
			printf(GREY "  %s\n", "(empty)" RESET);
		}
		print_list(current->flag, BLUE "Flags :" RESET);
		print_list(current->arg, BLUE "Arguments :" RESET);
		printf(YELLOW "Command_quote : %d\n" RESET, current->command_quote);
		print_string_array(current->final_group, BLUE "Final Group" RESET);
			// Fonction pour afficher final_group
		printf(ORANGE "_____________________________\n" RESET);
		current = current->next;
	}
}


void	print_separator(int test_number, const char *test_name)
{
	printf("\n%s===============================%s\n", CYAN, RESET);
	printf("%s[ TEST %d: %s ]%s\n", BOLD, test_number, test_name, RESET);
	printf("%s===============================%s\n\n", CYAN, RESET);
}

void	print_input_output(t_data *data)
{
	printf("%s| Input redirection: %s%s\n", CYAN,
		data->input.value ? data->input.value : "(none)", RESET);
	printf("%s| Output redirection: %s%s\n\n", CYAN,
		data->output.value ? data->output.value : "(none)", RESET);
}

void	print_commands(t_data *data)
{
	t_commands	*cmd;
	int			command_number;
	t_list		*arg;
	t_list		*flag;

	command_number = 1;
	cmd = data->command;
	printf("%s--- Parsed Commands ---\n%s", GREEN, RESET);
	while (cmd)
	{
		printf("%s| Command %d: %s%s\n", CYAN, command_number, RESET,
			cmd->command ? cmd->command : "(none)");
		if (cmd->arg)
		{
			printf("| Arguments: ");
			arg = cmd->arg;
			while (arg) {
				printf("[%s] ", arg->value);
				arg = arg->next;
			}
			printf("\n");
		}
		if (cmd->flag)
		{
			printf("| Flags: ");
			flag = cmd->flag;
			while (flag) {
				printf("[%s] ", flag->value);
				flag = flag->next;
			}
			printf("\n");
		}
		if (cmd->final_group)
		{
			printf("| Final Group: ");
			for (size_t i = 0; cmd->final_group[i]; i++) {
				printf("[%s] ", cmd->final_group[i]);
			}
			printf("\n");
		}
		cmd = cmd->next;
		command_number++;
		if (cmd) printf("\n");
	}
	printf("%s-----------------------\n\n%s", GREEN, RESET);
}


void	check_result(int *pass, int *total, int condition,
		const char *test_name)
{
	(*total)++;
	if (condition)
	{
		(*pass)++;
		printf("%s[PASS]%s %s\n", GREEN, RESET, test_name);
	}
	else
	{
		printf("%s[FAIL]%s %s\n", RED, RESET, test_name);
	}
}

void	test_command(int test_number, const char *command, t_data *data,
		int *pass, int *total, const char *expected_command,
		const char *test_name)
{
	int	result;

	ft_memset(data, 0, sizeof(t_data));
	data->line = ft_strdup(command);
	print_separator(test_number, test_name);
	printf("\033[4;37m> Command:\033[0m %s\n\n", command);
	lexer(data, 1);
	parser(data);
	print_commands(data);
	print_input_output(data);
	result = data->command && ft_strcmp(data->command->command,
			expected_command) == 0;
	check_result(pass, total, result, test_name);
}

void	test_command_from_argument(int argc, char **argv, t_data *data)
{
	char	*command;

	command = argv[1];
	if (argc < 2)
	{
		printf("Usage: ./minishell <command-to-test>\n");
		return ;
	}
	printf("%s\n===============================%s\n", CYAN, RESET);
	printf("%s       [ CUSTOM TEST ]%s\n", BOLD, RESET);
	printf("%s===============================%s\n", CYAN, RESET);
	printf("\n%s> Command:%s %s\n\n", UNDERL, RESET, command);
	ft_memset(data, 0, sizeof(t_data));
	data->line = command;
	if (lexer(data, 1) != EXIT_SUCCESS)
	{
		fprintf(stderr, "Lexer failed\n");
		return ;
	}
	if (parser(data) != EXIT_SUCCESS)
	{
		fprintf(stderr, "Parser failed\n");
		return ;
	}
	print_commands(data);
	print_input_output(data);
	printf("%s[?] Custom Command Test%s\n", PURPLE, RESET);
}

int	main(int ac, char **av)
{
	t_data data;
	int total_tests = 0;
	int pass_tests = 0;

	printf("\n%sParser Tester%s\n", BOLD, RESET);

	if (ac > 1)
	{
		test_command_from_argument(ac, av, &data);
		return (0);
	}
	else
	{
		test_command(1, "ls", &data, &pass_tests, &total_tests, "ls",
			"Simple Command");
		test_command(2, "echo Hello", &data, &pass_tests, &total_tests, "echo",
			"Command with Argument");
		test_command(3, "echo \"Hello, World!\"", &data, &pass_tests,
			&total_tests, "echo", "Command with Quotes");

		test_command(4, "ls | grep main", &data, &pass_tests, &total_tests,
			"ls", "Pipeline Command");
		test_command(5, "echo Test > test.txt", &data, &pass_tests,
			&total_tests, "echo", "Redirection Output");
		test_command(6, "cat < test.txt", &data, &pass_tests, &total_tests,
			"cat", "Redirection Input");
		test_command(7, "echo More >> test.txt", &data, &pass_tests,
			&total_tests, "echo", "Append Redirection");
		test_command(8, "echo $USER", &data, &pass_tests, &total_tests, "echo",
			"Variable Expansion");
		test_command(9, "echo $?", &data, &pass_tests, &total_tests, "echo",
			"Exit Status Variable");
		test_command(10, "ls --l -a", &data, &pass_tests, &total_tests, "ls",
			"Command with Multiple Arguments");
		test_command(11, "ls | grep main | wc -l", &data, &pass_tests,
			&total_tests, "ls", "Multiple Pipelines");
		test_command(12, "echo \"Nested 'quotes' test\"", &data, &pass_tests,
			&total_tests, "echo", "Nested Quotes");
		test_command(13, "echo $USER > user.txt", &data, &pass_tests,
			&total_tests, "echo", "Redirection with Variable");
		test_command(14, "echo \"\"", &data, &pass_tests, &total_tests, "echo",
			"Empty Argument");
		test_command(15, "grep -i main", &data, &pass_tests, &total_tests,
			"grep", "Command with Flag");
		test_command(16, "| ls", &data, &pass_tests, &total_tests, NULL,
			"Invalid Syntax: Pipe at Start");
		// test_command(17, "ls |", &data, &pass_tests, &total_tests, NULL,
			"Invalid Syntax: Pipe at End");
		test_command(18, "echo \"Unclosed quote", &data, &pass_tests,
			&total_tests, NULL, "Unclosed Quote");
		test_command(19, "echo Test | grep T > output.txt", &data, &pass_tests,
			&total_tests, "echo", "Complex Command");
		test_command(20, "cat file.txt | grep 'pattern' > output.txt", &data,
			&pass_tests, &total_tests, "cat", "Pipeline with Redirection");
		test_command(21, "cat < input.txt > output.txt", &data, &pass_tests,
			&total_tests, "cat", "Input and Output Redirection");
		test_command(22, "ls > file1.txt > file2.txt", &data, &pass_tests,
			&total_tests, "ls", "Multiple Output Redirections");
		test_command(23, "grep 'pattern' < file.txt", &data, &pass_tests,
			&total_tests, "grep 'pattern'", "Input Redirection with grep");
		test_command(24, "ls | sort | uniq", &data, &pass_tests, &total_tests,
			"ls | sort | uniq", "Pipeline with Multiple Filters");
		test_command(25, "echo Test | grep T > output.txt", &data, &pass_tests,
			&total_tests, "echo Test | grep T",
			"Redirection and Pipeline Combined");
		test_command(26, "cat < input.txt >> output.txt", &data, &pass_tests,
			&total_tests, "cat", "Append and Input Redirection");
		test_command(27, "echo Append >> output1.txt >> output2.txt", &data,
			&pass_tests, &total_tests, "echo Append",
			"Multiple Append Redirections");
		test_command(28, "ls | grep main | sort > result.txt", &data,
			&pass_tests, &total_tests, "ls | grep main | sort",
			"Pipeline with Output Redirection");
		test_command(29, "cat file1.txt file2.txt > combined.txt", &data,
			&pass_tests, &total_tests, "cat file1.txt file2.txt",
			"Multiple Input Files to Single Output");
		test_command(30, "grep -i 'pattern' file.txt >> results.txt", &data,
			&pass_tests, &total_tests, "grep -i 'pattern'",
			"Case-Insensitive Grep with Append Redirection");
		test_command(31, "sort < unsorted.txt > sorted.txt", &data, &pass_tests,
			&total_tests, "sort", "Sort with Input and Output Redirection");
		test_command(32, "echo 'Multiline\nText' | grep Text > filtered.txt",
			&data, &pass_tests, &total_tests,
			"echo 'Multiline\nText' | grep Text",
			"Pipeline with Multiline Echo");
		test_command(33, "echo Hello > temp1.txt | echo World >> temp1.txt",
			&data, &pass_tests, &total_tests, "echo Hello > temp1.txt
			&& echo World >> temp1.txt",
			"Concatenated Echo Commands with Redirection");
		test_command(34, "ls -l | grep 'test' | wc -l > count.txt", &data,
			&pass_tests, &total_tests, "ls -l | grep 'test' | wc -l",
			"Pipeline with Word Count and Output Redirection");
		test_command(35, "awk '/pattern/ {print $1}' < data.txt > result.txt",
			&data, &pass_tests, &total_tests, "awk '/pattern/ {print $1}'",
			"AWK with Input and Output Redirection");

		// Here_doc tests
		test_command(36, "cat << EOF", &data, &pass_tests, &total_tests, "cat",
			"Here-Doc with Simple Input");
		test_command(37, "cat << 'EOF'", &data, &pass_tests, &total_tests,
			"cat", "Here-Doc with Quoted Input");
		test_command(38, "cat << EOF | grep 'pattern'", &data, &pass_tests,
			&total_tests, "cat", "Here-Doc Combined with Pipeline");
		test_command(39, "<< EOF cat", &data, &pass_tests, &total_tests, "cat",
			"Here-Doc with Syntax Variation");
		test_command(40, "cat << EOF > output.txt", &data, &pass_tests,
			&total_tests, "cat", "Here-Doc with Redirection");
		test_command(41, "cat << coucouloulou | wc -l", &data, &pass_tests,
			&total_tests, "cat", "Heredoc Piped to Word Count");
		test_command(42, "grep << EOF >> output.txt", &data, &pass_tests,
			&total_tests, "grep", "Heredoc Appended to Output File");
		test_command(43, "cat << EOF | grep pattern >> filtered_results.txt",
			&data, &pass_tests, &total_tests, "cat",
			"Heredoc Piped to Grep and Appended");
		test_command(44, "sort << EOF > sorted_output.txt", &data, &pass_tests,
			&total_tests, "sort", "Heredoc Input Sorted and Written to File");
		test_command(45, "awk '/pattern/ {print $2}' << EOF", &data,
			&pass_tests, &total_tests, "awk",
			"Heredoc Processed by AWK Command");


		printf("\n%s=== Test Summary ===%s\n", PURPLE, RESET);
		printf("Total Tests: %s%d%s\n", CYAN, total_tests, RESET);
		printf("Passed: %s%d%s\n", pass_tests == total_tests ? GREEN : YELLOW,
			pass_tests, RESET);
		printf("Failed: %s%d%s\n", total_tests - pass_tests == 0 ? GREEN : RED,
			total_tests - pass_tests, RESET);

		return (0);
	}
}*/
