/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 02:03:36 by thugo             #+#    #+#             */
/*   Updated: 2017/11/01 19:04:28 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "types.h"

int		builtin_pwd(t_data *data, int argc, char **argv);
int		builtin_exit(t_data *data, int argc, char **argv);
int		builtin_cd(t_data *data, int argc, char **argv);
int		builtin_env(t_data *data, int argc, char **argv);
int		builtin_setenv(t_data *data, int argc, char **argv);
int		builtin_unsetenv(t_data *data, int argc, char **argv);
int		builtin_echo(t_data *data, int argc, char **argv);

#endif
