/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:22:44 by femorell          #+#    #+#             */
/*   Updated: 2023/03/13 15:22:46 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*array;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	array = 0;
	if (s1 && set)
	{
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && i < j)
			j--;
		array = (char *)malloc(sizeof(char) * (j - i + 1));
		if (array)
			ft_strlcpy(array, &s1[i], (j - i + 1));
	}
	return (array);
}

/*int	main()
{
	char array[] = "111222114242411";
	char set[] = "111";
	
	printf("%s", ft_strtrim(array, set));
}*/
