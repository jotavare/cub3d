/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:33:58 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:21:11 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates and initializes a block of memory for an array of elements.
 *
 * @param count The number of elements to allocate.
 * @param size The size of each element in bytes.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size > 0 && count > ULONG_MAX / size)
		return (0);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}
