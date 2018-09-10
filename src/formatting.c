/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 16:50:13 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:58:02 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <assembler/include/asm.h>

/*
**	This will "delete" a character from the middle of a string by allocating
**	a new string(one character shorter), copying all characters from the old
**	string(but skipping over the "deleted" char), deleting the old string, and
**	returning a pointer to the new string.
*/

static char		*del_char(char *line, int offset)
{
	char	*new;
	int		i;
	int		f;

	new = ft_strnew(ft_strlen(line) - 1);
	i = 0;
	f = 0;
	while (line[f])
	{
		if (f == offset)
			f++;
		new[i] = line[f];
		i++;
		f++;
	}
	new[i] = '\0';
	ft_strdel(&line);
	return (new);
}

/*
**	This function will look for the end of a label and change the space to a \n.
*/

static void		newline_label(char *line)
{
	int	i;

	i = 0;
	while (line[i] != LABEL_CHAR)
		i++;
	line[i + 1] = '\n';
}

/*
**	This function will trim a line(delete extraneous white space from the front
**	and back), replace all tabs and newlines with spaces, and delete duplicate
**	spaces. Thus, when a line is passed through this function, it should be
**	perfectly formatted. For example:
**	"label:
**	 sti r1, 2, %3"
*/

char			*format_line(char *line)
{
	char			*result;
	unsigned int	i;

	if (!(line[0] && identify_line(line) != 2 && identify_line(line) != 3))
		return (line);
	i = 1;
	find_replace(';', '\0', line);
	find_replace('#', '\0', line);
	find_replace('\t', ' ', line);
	find_replace('\n', ' ', line);
	find_replace(',', ' ', line);
	result = ft_strtrim(line);
	ft_strdel(&line);
	while (result[i - 1] && result[i])
	{
		if (result[i] == ' ' && result[i - 1] == ' ')
		{
			result = del_char(result, i);
			i = 0;
		}
		i++;
	}
	if (identify_line(result) == 5)
		newline_label(result);
	return (result);
}
