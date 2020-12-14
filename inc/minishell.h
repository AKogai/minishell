/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "libft.h"

typedef struct			s_shell
{
	char	**genvv;
}						t_sh;

void					change_dir(char *path, int print_path, t_sh *env);
int						cd_builtin(char **command, t_sh *env);
void					exit_shell(t_sh *env);
char					*parse_home_path(char *path, int reverse_parse,
	t_sh *env);
void					display_prompt_msg(t_sh *env);
int						echo_builtin(char **command);
int						exec_command(char **command, t_sh *env);
int						find_env_var(char *var, t_sh *env);
char					*get_env_var(char *var, t_sh *env);
char					**realloc_envv(int new_size, t_sh *env);
void					set_env_var(char *key, char *value, t_sh *env);
int						setenv_builtin(char **args, t_sh *env);
void					print_env(char **env);
int						unsetenv_builtin(char **command, t_sh *env);
int						ft_isquote(char x);
t_sh					*init_envv(int ac, char **av, char **envv);
int						envv_len(char **envv);
#endif
