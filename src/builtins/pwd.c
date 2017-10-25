/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:08:55 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 02:14:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
#include "minishell.h"

int	builtin_pwd(t_data *data, int argc, char **argv)
{
	char	cwd[MAXPATHLEN];

	(void)data;
	(void)argc;
	(void)argv;
	if (!getcwd(cwd, MAXPATHLEN))
		return (EXIT_FAILURE);
	ft_putendl(cwd);
	return (EXIT_SUCCESS);
}
