/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:32:06 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:56:12 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft/libft.h>

/*
**	Writes len data into the temporary array. Updates cursor as it goes. It will
**	verify that the data will not exceed CHAMP_MAX_SIZE before it starts. If
**	the data is too large, the program will display an error and exit.
*/

void	write_out(char *data, unsigned int len)
{
	unsigned int	i;

	if (g_cursor_out + len > CHAMP_MAX_SIZE)
	{
		ft_putendl("ERROR: Champion too large!");
		cleanup();
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
		g_temp_out[g_cursor_out++] = data[i++];
}

void	out_error(char *filename)
{
	ft_putstr("Error opening \"");
	ft_putstr(filename);
	ft_putendl("\" for writing.");
	cleanup();
	exit(EXIT_FAILURE);
}

/*
**	This function will write the contents of the temporary array to a file.
*/

_Bool	write_file(char *filename)
{
	int				fd;
	unsigned int	i;
	t_header		*header;

	fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		out_error(filename);
	header = generate_header(COREWAR_EXEC_MAGIC, g_prog_name, g_cursor_out,
		g_prog_comment);
	write(fd, header, sizeof(t_header));
	ft_memdel((void **)&header);
	i = 0;
	while (i < g_cursor_out)
		write(fd, g_temp_out + i++, 1);
	ft_putstr("Name:    \"");
	ft_putstr(g_prog_name);
	ft_putstr("\"\nComment: \"");
	ft_putstr(g_prog_comment);
	ft_putstr("\"\n\"");
	ft_putstr(g_filename_out);
	ft_putendl("\" successfully assembled!");
	return (1);
}
