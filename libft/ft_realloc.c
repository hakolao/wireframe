/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:26:04 by ohakola           #+#    #+#             */
/*   Updated: 2019/10/29 14:33:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Change the size of the block referenced by ptr to "size",
** possibly moving the block to a larger storage area.
*/

void	*ft_realloc(void *ptr, size_t size_in, size_t size_out)
{
	void *out;

	if (ptr == 0)
		return (ft_memalloc(size_out));
	if (size_out <= size_in)
		return (ptr);
	if (!(out = ft_memalloc(size_out)))
		return (NULL);
	ft_memcpy(out, ptr, size_in);
	free(ptr);
	ptr = NULL;
	return (out);
}
