/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jotavare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:34:01 by jotavare          #+#    #+#             */
/*   Updated: 2023/11/04 18:21:58 by jotavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character represents a decimal digit (0-9).
 *
 * @param str The character to check.
 * @return 1 if the character is a digit, 0 otherwise.
 */
int	ft_isdigit(int str)
{
	return (str >= '0' && str <= '9');
}
