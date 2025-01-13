#include "../../includes/minishell.h"

// int main(int argc, char **argv, char **envp)
// {
//     t_data data;
//     char buffer[1024];
//     ssize_t bytes_read;

//     if (init_data(&data, envp))
//     {
//         fprintf(stderr, "Failed to initialize data.\n");
//         return (EXIT_FAILURE);
//     }
//     if (argc < 2)
//     {
//         fprintf(stderr, "Usage: %s <delimiter>\n", argv[0]);
// 		// free_data(&data);
//         return (EXIT_FAILURE);
//     }
//     data.input.value = argv[1]; // Délimiteur fourni en argument
//     printf("Starting here_doc. Type '%s' to stop.\n", data.input.value);
//     if (here_doc(&data) == EXIT_FAILURE)
//     {
//         fprintf(stderr, "here_doc failed.\n");
//         return (EXIT_FAILURE);
//     }
//     printf("\nContent of heredoc:\n");
//     while ((bytes_read = read(data.input.fd, buffer, sizeof(buffer)
//			- 1)) > 0)
//     {
//         buffer[bytes_read] = '\0';
//         printf("%s", buffer);
//     }
//     close(data.input.fd);
//     // free_data(&data);
// 	return (EXIT_SUCCESS);
// }

// void free_data(t_data *data)
// {
//     if (data->full_path)
//     {
//         free(data->full_path);
//         data->full_path = NULL;
//     }
//     if (data->input.value)
//     {
//         free(data->input.value);
//         data->input.value = NULL;
//     }
//     if (data->output.value)
//     {
//         free(data->output.value);
//         data->output.value = NULL;
//     }
//     free_env_list(data->env);
//     data->env = NULL;
// }
