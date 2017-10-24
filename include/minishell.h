/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:59:46 by thugo             #+#    #+#             */
/*   Updated: 2017/10/24 02:08:52 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ENV(elem) ((t_env *)elem->content)
# define CMD(elem) ((t_cmds *)elem->content)

# include "types.h"

void			env_init(t_data *data, char **environ);
void			env_unset(t_data *data, const char *name);
char			*env_getset(t_data *data, const char *name, const char *value);
char			**env_getarray(t_data *data);
int				builtins(t_data *data, const char *cmd, int argc, char **argv);
void			loop(t_data *data);
void			ms_cerror(char *errmsg);
void			prompt(t_data *data);
void			parse_line(t_data *data, t_cmd ***cmds, char *line);

#endif
