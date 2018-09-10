/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 08:42:14 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:51:46 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <assembler/include/asm.h>
#include <stdlib.h>

/*
**	This function will simply look for a character in a string and if found,
**	replace it with another character.
*/

void		find_replace(char find, char replace, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == find)
			string[i] = replace;
		i++;
	}
}

/*
**	This function just outputs an error message and cleanly exits in the event
**	that the input file can't be opened.
*/

void		read_error(char *filename)
{
	ft_putstr("ERROR: Can't open \"");
	ft_putstr(filename);
	ft_putendl("\".");
	cleanup();
	exit(EXIT_FAILURE);
}

/*
**	This function converts the .s extension to the .cor extension for the
**	filename.
*/

void		gen_filename(void)
{
	int	len;

	len = ft_strlen(g_filename_in);
	g_filename_out = ft_strnew(len + 2);
	ft_strcpy(g_filename_out, g_filename_in);
	g_filename_out[len - 1] = 'c';
	g_filename_out[len + 0] = 'o';
	g_filename_out[len + 1] = 'r';
}

/*
**	This function makes sure the filename ends in a ".s". If not, it
**	automatically adds it.
*/

void		preprocess_filename(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	if (filename[len - 2] == '.' && filename[len - 1] == 's')
		g_filename_in = ft_strdup(filename);
	else
	{
		g_filename_in = ft_strnew(len + 2);
		ft_strcpy(g_filename_in, filename);
		g_filename_in[len] = '.';
		g_filename_in[len + 1] = 's';
	}
}

_Bool		verify_param(char *param)
{
	int	i;

	i = 1;
	if (param[0] == 'r')
	{
		if (ft_atoi(param + 1) > REG_NUMBER)
			return (0);
	}
	else if (param[0] == DIRECT_CHAR)
	{
		i = 1 + (param[1] == '-');
		if (param[1] == LABEL_CHAR)
			return (1);
	}
	else if (param[0] != LABEL_CHAR)
		i = !(param[0] != '-');
	else
		return (1);
	while (param[i])
		if (!ft_isdigit(param[i++]))
			return (0);
	return (1);
}
