/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:22:49 by thugo             #+#    #+#             */
/*   Updated: 2017/04/13 18:25:07 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int			retval;
	va_list		ap;

	va_start(ap, format);
	retval = ft_vdprintf(1, format, &ap);
	va_end(ap);
	return (retval);
}
