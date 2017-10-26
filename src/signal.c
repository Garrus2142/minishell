/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 20:32:41 by thugo             #+#    #+#             */
/*   Updated: 2017/10/26 22:08:55 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

extern pid_t	g_runpid;

void	handle_sigint(int sig)
{
	if (g_runpid)
		kill(g_runpid, SIGINT);
}

void	handle_sigquit(int sig)
{
	if (g_runpid)
		kill(g_runpid, SIGQUIT);
}

void	handle_siginfo(int sig)
{
	if (g_runpid)
		kill(g_runpid, SIGINFO);
}

void	signal_init(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINFO, handle_siginfo);
}
