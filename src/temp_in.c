/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:55:38 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 13:04:29 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft/libft.h>
#include <fcntl.h>

/*
**	This function will write a string to the temp-file.
*/

static void		write_temp(char *s)
{
	static int	cursor;
	int			i;

	i = 0;
	while (s[i])
		g_temp_in[cursor++] = s[i++];
}

/*
**	This function will identify if the line passed to it is either a name or
**	comment command. If it is, then the appropriate function will be called to
**	set the variables. It returns 1 if it is a name or comment, otherwise 0.
*/

static _Bool	name_comment(char *line)
{
	_Bool	result;
	char	*temp;

	result = 0;
	temp = ft_strdup(line);
	temp = format_line(temp);
	if (identify_line(temp) == 2)
	{
		read_name(line);
		result = 1;
	}
	else if (identify_line(temp) == 3)
	{
		read_comment(line);
		result = 1;
	}
	ft_strdel(&temp);
	return (result);
}

/*
**	This function will create the temp-space in memory, read the input file
**	through the preprocessor line-by-line, and save it into the temp-space. It
**	also closes the input file on completion. (It shouldn't be needed again.)
**	A pointer to the temp-space will be put in g_temp_in.
**	Note: This is not the most efficient way possible to do this due to the
**	allocated space not being completely used(some whitespace will be trimmed
**	during preprocessing). But it is the simplest solution requiring the least
**	memory operations.
*/

void			read_file(char *filename)
{
	char	*line;
	int		fd;
	int		ln;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		read_error(filename);
	g_temp_in = ft_strnew(lseek(fd, 0, SEEK_END));
	lseek(fd, 0, SEEK_SET);
	ln = 0;
	while (get_next_line(fd, &line) == 1)
	{
		++ln;
		if (line[0] && !name_comment(line) && line[0] != COMMENT_CHAR)
		{
			check_error(ln, line);
			line = format_line(line);
			write_temp(line);
			write_temp("\n");
		}
		ft_strdel(&line);
	}
	close(fd);
	write_temp("\0");
}

/*
**	This function is basically GNL except that it reads from the temp_in
**	instead of a file_descriptor. It's similar to ft_strdup except it stops at
**	a null byte OR a newline.
*/

int				get_temp_line(char **str)
{
	int			i;
	int			end;

	end = g_cursor_in;
	i = 0;
	while (g_temp_in[end] && g_temp_in[end] != '\n')
		end++;
	if (!g_temp_in[end])
		return (0);
	*str = ft_strnew(end - g_cursor_in);
	while (g_temp_in[g_cursor_in] &&
	g_temp_in[g_cursor_in] != '\n')
		(*str)[i++] = g_temp_in[g_cursor_in++];
	g_cursor_in++;
	return (1);
}

/*
**	This function simply sets the get_temp_line cursor to a specific position.
*/

void			lseek_temp(unsigned int cursor)
{
	g_cursor_in = cursor;
}
