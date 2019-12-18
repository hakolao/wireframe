/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:53:20 by ohakola           #+#    #+#             */
/*   Updated: 2019/12/17 15:09:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrix.h"

void	ft_putdouble(double num)
{
	short i;
	int tmp;
	short size;
	char *str;

	i = 0;
	size = 1;
	tmp = (int)(num * 100);
	if (num == .0)
	{
		ft_putstr("0.00");
		return ;
	}
	if (num < .0 && (tmp *= -1.) > 0)
		++size;
	num = tmp;
	while (tmp != 0 && ++size != 0)
		tmp /= 10;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return;
	str[size--] = 0;
	while ((int)num != 0 && ++i > 0)
		(i != 3 && (str[size--] = ((int)num % 10) + '0')) ? (num /= 10) : (str[size--] = '.');
	(size == 0 && i == 2) ? str[0] = '.' : 1;
	(size == 0 && i != 2) ? str[0] = '-' : 1;
	write(1, str, ft_strlen(str));
	free(str);
}
