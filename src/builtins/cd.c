/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:43:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 02:47:11 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int		builtin_cd(t_data *data, int argc, char **argv)
{
	if (argc > 0)
		chdir(argv[0]);
	return (0);
}
