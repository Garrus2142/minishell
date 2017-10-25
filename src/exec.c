/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 01:55:07 by thugo             #+#    #+#             */
/*   Updated: 2017/10/25 15:21:02 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	exec_execute(t_data *data, char **cmd)
{
	if (builtin_execute(data, cmd))
		return ;
	else
	{
		data->exec_stat = 127;
		ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n",
			cmd[0]);
	}
}
