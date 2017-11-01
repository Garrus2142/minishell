/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 21:13:57 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 21:22:25 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include "libft.h"

typedef struct	s_env
{
	char	*name;
	char	*value;
}				t_env;

typedef struct	s_data
{
	t_list	*env;
	char	**envtab;
	char	exit;
	char	*cwd;
	char	exec_stat;
	pid_t	runpid;
}				t_data;

typedef struct	s_builtin
{
	char	*name;
	int		(*fn)(t_data*, int, char**);
}				t_builtin;

#endif
