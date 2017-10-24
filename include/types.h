/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 21:13:57 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 16:35:54 by thugo            ###   ########.fr       */
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
}				t_data;

typedef struct	s_cmd
{
	char	*name;
	char	**args;
}				t_cmd;

#endif
