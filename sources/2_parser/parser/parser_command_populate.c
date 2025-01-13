
#include "minishell.h"

/**
 * @brief Remplit le noeud de commande avec la valeur et la quote du token.
 *
 * @param node Le noeud de commande à remplir.
 * @param token Token contenant les informations de la commande.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE sinon.
 */
int	populate_node_command(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	node->command = ft_strdup(token->value);
	if (!node->command)
		return (EXIT_FAILURE);
	node->command_quote = token->quote;
	return (EXIT_SUCCESS);
}

/**
 * @brief Ajoute un flag au noeud de commande.
 *
 * @param node Le noeud de commande à modifier.
 * @param token Token contenant le flag à ajouter.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE sinon.
 */
int	populate_node_flag(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	if (add_new_list_node(&node->flag, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Ajoute un argument au noeud de commande,
 * 		sauf si la commande est "export".
 *
 * @param node Le noeud de commande à modifier.
 * @param token Token contenant l'argument à ajouter.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE sinon.
 */
int	populate_node_argument(t_commands *node, t_token *token)
{
	if (!node)
		return (EXIT_FAILURE);
	// if (ft_strcmp(node->command, "export"))
	// {
	// 	if (add_new_list_node(&node->arg, token))
	// 		return (EXIT_FAILURE);
	// }
	if (add_new_list_node(&node->arg, token))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
