/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 21:13:57 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 01:32:19 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	int		exec_stat;
}				t_data;

typedef struct	s_builtin
{
	char	*name;
	int		(*fn)(t_data*, int, char**);
}				t_builtin;

#endif
