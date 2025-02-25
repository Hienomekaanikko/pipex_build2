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

void	init_data(t_data *data)
{
	data->cmd = NULL;
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
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc == 5)
	{
		init_data(&data);
		prep_env(&data, argc, argv);
	}
	ft_exit(&data, "Invalid amount of arguments", 1);
}
