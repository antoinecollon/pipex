/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollon <acollon@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:53:22 by acollon           #+#    #+#             */
/*   Updated: 2025/04/13 16:39:26 by acollon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*sc;
	unsigned char		*dst;

	dst = (unsigned char *)dest;
	sc = (const unsigned char *)src;
	if (dst == sc)
		return (dest);
	if (dst < sc)
	{
		while (n--)
			*dst++ = *sc++;
	}
	else
	{
		while (n--)
			dst[n] = sc[n];
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	char	dest[50];
	char	*dst;

	if (ac == 2)
	{
		dst = ft_memmove(dest, av[1] + 7, 15);
		printf("Source : %s\n", av[1]);
		printf("Dest : %s\n", dst);
	}
	return (0);
}*/
