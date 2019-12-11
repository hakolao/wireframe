/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:06:36 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/11 13:07:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Converts traditional R G B
** value to single integer form.
*/

int		ft_rgbtoi(int red, int green, int blue)
{
	return ((red & 255) << 16) | ((green & 255) << 8 | (blue & 255));
}
