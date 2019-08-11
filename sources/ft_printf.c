/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 00:15:52 by ujyzene           #+#    #+#             */
/*   Updated: 2019/06/30 00:25:33 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int ft_printf(const char *format, ...)
{
	int count;
	va_list args;

	va_start(args, format);
	count = pf_vprintf((char*)format, args);
	va_end(args);
	return (count);
}

/*
** for more printf funcs
*/
