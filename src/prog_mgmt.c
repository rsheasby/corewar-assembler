/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_mgmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 19:01:49 by rsheasby          #+#    #+#             */
/*   Updated: 2017/11/06 09:36:25 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft/libft.h>

/*
**	This function will allocate a space for the global variables struct and
**	call read_file to store the preprocessed file contents into the temp_in.
*/

void	initialize(char *filename)
{
	g_prog_name[0] = 0;
	g_prog_comment[0] = 0;
	preprocess_filename(filename);
	ft_putstr("Assembling \"");
	ft_putstr(g_filename_in);
	ft_putendl("\".");
	gen_filename();
	read_file(g_filename_in);
	if (!g_prog_name[0])
	{
		ft_putendl("No program name specified.");
		exit(EXIT_FAILURE);
	}
	else if (!g_prog_comment[0])
	{
		ft_putendl("No program comment specified.");
		exit(EXIT_FAILURE);
	}
}

/*
**	This function will set the g_prog_name variable to the contents of the
**	quotation marks in the string passed to it. It assumes that the line has
**	already correctly been identified as a name command.
*/

void	read_name(char *line)
{
	int	offset;
	int	i;

	offset = 0;
	i = 0;
	while (i < PROG_NAME_LENGTH)
		g_prog_name[i++] = '\0';
	i = 0;
	while (line[offset] != '"' && line[offset])
		offset++;
	offset++;
	while (line[offset + i] != '"' && line[offset + i])
	{
		g_prog_name[i] = line[offset + i];
		i++;
	}
}

/*
**	This function will set the g_prog_comment string to the contents of the
**	quotation marks in the string passed to it. It assumes that the line has
**	already correctly been identified as a comment command.
*/

void	read_comment(char *line)
{
	int	offset;
	int	i;

	offset = 0;
	i = 0;
	while (i < COMMENT_LENGTH)
		g_prog_comment[i++] = '\0';
	i = 0;
	while (line[offset] != '"' && line[offset])
		offset++;
	offset++;
	while (line[offset + i] != '"' && line[offset + i])
	{
		g_prog_comment[i] = line[offset + i];
		i++;
	}
}

/*
**	This frees all necessary memory before closing.
*/

void	cleanup(void)
{
	ft_strdel(&(g_temp_in));
	ft_strdel(&g_filename_in);
	ft_strdel(&g_filename_out);
	delete_labels(g_labels);
}
