/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 15:32:51 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int		builtin_cd(t_data *data, int argc, char **argv)
{
	(void)data;
	if (argc > 1)
		chdir(argv[1]);
	return (0);
}
