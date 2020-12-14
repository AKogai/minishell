/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_stcheck(char *x, char *home_path, t_sh *env)
{
	if (!x)
	{
		if (!(home_path == NULL))
			change_dir(home_path, 0, env);
		else
			ft_putendl("HOME not set");
		return (1);
	}
	return (0);
}

static void		print_pth(char *path, t_sh *env)
{
	char	*parsed_home;

	parsed_home = parse_home_path(path, 0, env);
	ft_putstr(parsed_home);
	free(parsed_home);
}

void			change_dir(char *path, int print_path, t_sh *env)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (print_path)
		{
			print_pth(path, env);
			ft_putchar('\n');
		}
		set_env_var("OLDPWD", cwd, env);
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
}

static int		has_two_args(char **args, t_sh *env)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*tmp;

	if (args[1])
	{
		if (args[2])
		{
			ft_putendl("cd: too many arguments");
			return (1);
		}
		cwd = getcwd(buff, 4096);
		if (!(tmp = ft_strreplace(cwd, args[0], args[1])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(args[0]);
			free(tmp);
			return (1);
		}
		change_dir(tmp, 1, env);
		free(tmp);
		return (1);
	}
	return (0);
}

int				cd_builtin(char **args, t_sh *env)
{
	char	*home_path;

	home_path = get_env_var("HOME", env);
	if (ft_stcheck(args[0], home_path, env))
		return (1);
	if (has_two_args(args, env))
		return (1);
	else
	{
		if (ft_strequ(args[0], "--"))
		{
			change_dir(home_path, 0, env);
			return (1);
		}
		else if (args[0][0] == '-' && !args[0][2])
		{
			change_dir(get_env_var("OLDPWD", env), 1, env);
			return (1);
		}
		change_dir(args[0], 0, env);
	}
	return (1);
}
