/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:03:01 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 16:34:33 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

char	access_check(const char *path)
{
	char	check;

	check = 0;
	if (access(path, F_OK))
		check |= ACCESS_EXIST;
	if (access(path, X_OK))
		check |= ACCESS_EXEC;
	return (check);
}
