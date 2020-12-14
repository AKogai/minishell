/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijanie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:20:44 by ijanie            #+#    #+#             */
/*   Updated: 2020/05/09 17:21:53 by ijanie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*parse_env_var(char *str, int pos, t_sh *env)
{
	char	*value;
	char	*key;
	char	c;

	key = ft_strnew(1);
	while (str[pos] && !ft_isspace(str[pos]))
	{
		c = str[pos];
		key = ft_strjoinchcl(key, c);
		pos++;
	}
	if (!(value = get_env_var(key, env)))
	{
		free(key);
		return (NULL);
	}
	free(key);
	return (value);
}

static char		*parse_input(char *input, t_sh *env)
{
	int		i;
	char	*new;

	i = -1;
	new = ft_strnew(1);
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			new = ft_strjoincl(new, parse_env_var(input, i + 1, env), 0);
			while (input[i + 1] && !ft_isspace(input[i + 1]) &&
				input[i + 1] != '$')
				i++;
		}
		else if (((i != 0 && ft_isspace(input[i - 1])) || i == 0) &&
			input[i] == '~')
		{
			new = ft_strjoincl(new, parse_home_path(input + i, 1, env), 1);
			i += ft_strlen(input + i) - 1;
		}
		else
			new = ft_strjoinchcl(new, input[i]);
	}
	free(input);
	return (new);
}

int				ft_exec(char **commands, t_sh *env)
{
	int		i;
	int		ret;
	char	**command;

	i = -1;
	ret = 0;
	while (commands[++i])
	{
		command = ft_strsplitall(commands[i]);
		ret = exec_command(command, env);
		ft_freestrarr(command);
		if (ret == -1)
			break ;
	}
	return (ret);
}

static void		ft_input(char **input, t_sh *env)
{
	int		ret;
	char	buf;
	int		i;
	int		count;

	*input = ft_strnew(1);
	count = 1;
	i = 0;
	while ((ret = read(0, &buf, 1)) && buf != '\n')
	{
		*(*input + i++) = buf;
		*input = ft_realloc(*input, count, count + 1);
		count++;
	}
	*(*input + i) = '\0';
	if (!ret)
	{
		free(*input);
		exit_shell(env);
	}
	if ((ft_strchr(*input, '$') != NULL) || (ft_strchr(*input, '~') != NULL))
		*input = parse_input(*input, env);
}

int				main(int ac, char **av, char **envv)
{
	char	*input;
	int		res;
	char	**command;
	t_sh	*env;

	env = init_envv(ac, av, envv);
	while (42)
	{
		display_prompt_msg(env);
		ft_input(&input, env);
		if (ft_isemptystr(input, 1))
		{
			free(input);
			continue ;
		}
		command = ft_strsplit(input, ';');
		free(input);
		res = ft_exec(command, env);
		ft_freestrarr(command);
		if (res == -1)
			break ;
	}
	ft_freestrarr(env->genvv);
	free(env);
	return (0);
}
