/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bertille <bertille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:37:13 by uzanchi           #+#    #+#             */
/*   Updated: 2025/01/16 17:46:32 by bertille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char *ft_strstr(const char *str, const char *substr)
{
    const char *start;
    const char *pattern;

    start = str;
    pattern = substr;
    if (!str || !substr)
        return (NULL);
    while (str) 
    {

        while (start && pattern && start ==pattern) 
        {
            start++;
            pattern++;
        }
        if (!pattern)
            return ((char *)str);
        str++;
    }
    return (NULL);
}

