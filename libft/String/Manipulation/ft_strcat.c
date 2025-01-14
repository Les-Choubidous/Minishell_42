#include "../../libft.h"

void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!dst || !src)
		return ;
	len = ft_strlen(dst);
	i = len;
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return ;
}
