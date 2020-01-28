/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.helsinki.fi>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:12:33 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/28 18:15:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		z_shift(t_list *vtx_lst)
{
	double		sum;
	double		count;

	sum = 0;
	count = 0;
	while (vtx_lst)
	{
		sum += ((t_vector*)vtx_lst->content)->v[2];
		vtx_lst = vtx_lst->next;
		count++;
	}
	return (sum / count);
}
