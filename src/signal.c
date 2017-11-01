/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:32:41 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 18:12:52 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "minishell.h"

static t_data	*g_data;

void	handle_signal(int sig)
{
	if (!g_data->runpid)
	{
		ft_putchar('\n');
		g_data->exec_stat = 128 + sig;
		prompt_print(g_data);
	}
}

void	signal_init(t_data *data)
{
	g_data = data;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGINFO, handle_signal);
}
