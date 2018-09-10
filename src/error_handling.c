/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 22:09:35 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:57:51 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>
#include <stdlib.h>

/*
**	This function just outputs an error message and cleanly exits.
*/

static void		error(int ln, char *line, char *error_msg)
{
	ft_putstr(error_msg);
	ft_putstr(" at line ");
	ft_putnbr(ln);
	ft_putstr(":\n");
	ft_putstr(line);
	ft_putstr("\n");
	ft_strdel(&line);
	cleanup();
	exit(EXIT_FAILURE);
}

/*
**	This function counts how many parameters there are. If it doesn't match the
**	definition in op.c, then it'll display an error and cleanly exit.
*/

void			verify_params_num(int ln, char *line, char *clean_line)
{
	char	**words;
	int		wordcount;

	if (identify_line(clean_line) == 5)
	{
		while (*clean_line && *clean_line != '\n')
			++clean_line;
		++clean_line;
	}
	else if (!clean_line[0])
		return ;
	words = ft_strsplit(clean_line, ' ');
	wordcount = 0;
	while (words[wordcount])
		++wordcount;
	if (wordcount > instruction_params_num(words[0]) + 1)
		error(ln, line, "Too many parameters");
	if (wordcount < instruction_params_num(words[0]) + 1)
		error(ln, line, "Too few parameters");
	ft_strarrdel(&words);
}

/*
**	This function will work out what the acceptable types are from the int,
**	(similar to how chmod's numeric codes work), and compare the param to the
**	acceptable list. If allowed, it returns true. Otherwise, it returns false.
*/

static _Bool	compare_type(short type, char *param)
{
	_Bool	ind;
	_Bool	dir;
	_Bool	reg;

	ind = 0;
	dir = 0;
	reg = 0;
	if (type >= T_IND)
	{
		ind = 1;
		type -= T_IND;
	}
	if (type >= T_DIR)
	{
		dir = 1;
		type -= T_DIR;
	}
	if (type)
		reg = 1;
	if (param[0] == 'r')
		return (reg);
	else if (param[0] == DIRECT_CHAR)
		return (dir);
	else
		return (ind);
}

/*
**	This function verifies each of the parameters one at a time. If the line
**	happens to be type 5(Label + instruction), then it'll move the string
**	pointer past the \n first. If an invalid instruction type is found, it'll
**	show an error message and cleanly exit.
*/

void			verify_params_type(int ln, char *line, char *clean_line)
{
	char	**words;
	short	*param_types;
	int		i;

	if (identify_line(clean_line) == 5)
	{
		while (*clean_line && *clean_line != '\n')
			++clean_line;
		++clean_line;
	}
	else if (!clean_line[0])
		return ;
	words = ft_strsplit(clean_line, ' ');
	i = 0;
	param_types = instruction_params_type(words[0]);
	while (words[++i])
		if (!compare_type(param_types[i - 1], words[i]) ||
		!verify_param(words[i]))
		{
			ft_putstr("Parameter ");
			ft_putnbr(i);
			error(ln, line, " invalid");
		}
	ft_strarrdel(&words);
}

/*
**	This function will check for most errors in one go. It verifies the
**	instruction is valid, checks if label definitions are using the allowed
**	alphabet, and verifies the correct amount of labels and the right types of
**	labels.
*/

void			check_error(int ln, char *line)
{
	int		linetype;
	char	*clean_line;

	clean_line = ft_strdup(line);
	clean_line = format_line(clean_line);
	linetype = identify_line(clean_line);
	if (linetype == 0 || linetype == 6)
		error(ln, line, "Invalid instruction");
	else if (linetype == 7)
		error(ln, line, "Label using invalid alphabet");
	else if (linetype == 4)
		return ;
	verify_params_num(ln, line, clean_line);
	verify_params_type(ln, line, clean_line);
	ft_strdel(&clean_line);
}
