/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:59:46 by thugo             #+#    #+#             */
/*   Updated: 2017/03/13 23:34:14 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ENV(elem) ((t_env *)elem->content)
# define CMD(elem) ((t_cmds *)elem->content)

# include "types.h"

void			env_init(t_data *data, char **environ);
char			*env_get(t_data *data, const char *name);
void			env_unset(t_data *data, const char *name);
void			env_set(t_data *data, const char *name, const char *value);
int				builtins(t_data *data, const char *cmd, int argc, char **argv);
void			parse_line(t_data *data, char **line, t_list **cmds);
void			loop(t_data *data);
void			ms_cerror(char *errmsg);

#endif
