/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ujyzene <ujyzene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:31:24 by ujyzene           #+#    #+#             */
/*   Updated: 2019/04/05 02:07:20 by ujyzene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *tmp;

	tmp = s1;
	s1 += ft_strlen(s1);
	while (n-- > 0 && *s2)
		*s1++ = *s2++;
	*s1 = 0;
	return (tmp);
}
