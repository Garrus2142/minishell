/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:35:33 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 15:32:32 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int		builtin_exit(t_data *data, int argc, char **argv)
{
	(void)data;
	(void)argc;
	(void)argv;
	close(STDIN_FILENO);
	return (0);
}
