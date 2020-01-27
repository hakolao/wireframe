/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:21:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/01/27 12:15:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** Logs input reading errors
*/

int				log_error(char *str, char *strerror)
{
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

/*
** Logs error using perror stdio function.
*/

int				log_perror(char *str)
{
	perror(str);
	return (1);
}
