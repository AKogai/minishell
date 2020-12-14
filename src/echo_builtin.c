/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		echo_out(char **str, int pos)
{
	int		starts_with;
	int		ends_with;
	int		str_len;

	starts_with = ft_isquote(str[pos][0]);
	str_len = (int)ft_strlen(str[pos]);
	ends_with = ft_isquote(str[pos][str_len - 1]);
	if (ends_with && starts_with)
		ft_putnstr(str[pos] + 1, -1);
	else if (ends_with)
		ft_putnstr(str[pos], -1);
	else if (starts_with)
		ft_putstr(str[pos] + 1);
	else
		ft_putstr(str[pos]);
	if (str[pos + 1])
		ft_putchar(' ');
}

int				echo_builtin(char **args)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!args[0])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
		n_flag = 1;
	i = -1;
	if (n_flag)
		++i;
	while (args[++i])
	{
		echo_out(args, i);
		if (!args[i + 1] && !n_flag)
			ft_putchar('\n');
	}
	return (1);
}

void			exit_shell(t_sh *env)
{
	ft_freestrarr(env->genvv);
	write(1, "\n", 1);
	exit(0);
}

char			*parse_home_path(char *path, int reverse_parse, t_sh *env)
{
	char	*home_path;
	char	*new;

	if (!path)
		return (NULL);
	home_path = get_env_var("HOME", env);
	if (home_path == NULL)
		reverse_parse ^= 1;
	if (!ft_strstartswith(path, reverse_parse ? "~" : home_path))
		return (ft_strdup(path));
	if (reverse_parse)
		new = ft_pathjoin(home_path, path + 1);
	else
	{
		if (*(path + ft_strlen(home_path)) == '\0')
			new = ft_strdup("~");
		else
			new = ft_pathjoin("~", path + ft_strlen(home_path));
	}
	return (new);
}

void			display_prompt_msg(t_sh *env)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*parsed_cwd;

	cwd = getcwd(buff, 4096);
	parsed_cwd = parse_home_path(cwd, 0, env);
	ft_putstr(parsed_cwd);
	free(parsed_cwd);
	ft_putstr(":");
}
