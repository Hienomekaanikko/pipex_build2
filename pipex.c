/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:29:06 by msuokas           #+#    #+#             */
/*   Updated: 2025/02/24 15:26:20 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, char *argv)
{
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->paths = NULL;
	data->path = NULL;
}

void	ft_exit(t_data *data, char *msg, int exitcode)
{
	if (data->paths)
		ft_free_split(data->paths);
	if (data->path)
		free(data->path);
	if (msg != NULL)
		perror(msg);
	exit(exitcode);
}

void	get_path(t_data *data, char *cmd, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		ft_exit(data, "path not found", 1);
	data->paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths, "/");
		data->path = ft_strjoin(path, cmd);
		free(path);
		if (access(data->path, F_OK | X_OK) == 0)
			return ;
		free(data->path);
		data->path = NULL;
		i++;
	}
	ft_exit(data, "command not found", 1);
}

void	prep_env(t_data *data, int argc, char **argv, char **envp)
{
	if (data->in = open(argv[1], O_RDONLY) < 0)
		ft_exit(data, "input fail", 1);
	if (data->out = open (argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644) < 0)
	{
		close(data->in);
		ft_exit(data, "output fail", 1);
	}
	if (pipe(data->pipe) < 0)
	{
		close(data->in);
		close(data->out);
		ft_exit(data, "pipe failed", 1);
	}
	get_path(data, data->cmd1, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 5)
	{
		init_data(&data, argv);
		prep_env(&data, argc, argv, envp);
	}
	ft_exit(&data, "Invalid amount of arguments", 1);
}
