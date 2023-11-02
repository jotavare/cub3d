/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:13 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/02 00:34:14 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	byte;

	byte = (char) c;
	while (*s && *s != byte && n)
	{
		s++;
		n--;
	}
	if (*s == byte)
		return ((char *)s);
	return (0);
}
