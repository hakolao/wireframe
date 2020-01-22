/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:06:36 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/22 19:00:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts traditional R G B
** value to single integer form.
*/

#include "libft.h"

int		ft_rgbtoi(int r, int g, int b)
{
	return ((r & 255) << 16) | ((g & 255) << 8 | (b & 255));
}
