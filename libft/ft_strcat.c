/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:08:18 by thugo             #+#    #+#             */
/*   Updated: 2016/11/08 15:40:56 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		i_s1;
	int		i_s2;

	i_s1 = ft_strlen(s1);
	i_s2 = 0;
	while (s2[i_s2] != '\0')
	{
		s1[i_s1] = s2[i_s2];
		i_s1++;
		i_s2++;
	}
	s1[i_s1] = '\0';
	return (s1);
}
