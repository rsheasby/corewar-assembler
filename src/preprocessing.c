/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 10:39:14 by rsheasby          #+#    #+#             */
/*   Updated: 2017/09/30 22:32:54 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <assembler/include/asm.h>

/*
**	This function calculates how many bytes "line" will take up when converted
**	to bytecode. It is very similar to process_line(), but it will increase the
**	counter where process_line() would write to the output file.
*/

static void	preprocess_line(char *line)
{
	char	**words;
	int		i;

	words = ft_strsplit(line, ' ');
	++g_cursor_preprocess;
	if (instruction_param_byte(words[0]) == 1)
		++g_cursor_preprocess;
	i = 0;
	while (words[++i] && i <= 3)
	{
		if (words[i][0] == 'r')
			g_cursor_preprocess += 1;
		else if (words[i][0] == DIRECT_CHAR && !instruction_index(words[0]))
			g_cursor_preprocess += 4;
		else
			g_cursor_preprocess += 2;
	}
	ft_strarrdel(&words);
}

/*
**	This function will preprocess the temp file line by line. If the line is
**	type 1(instruction) then it'll calculate how much space the line SHOULD take
**	up in the temp_out and increase the cursor. If the line is type 4(label)
**	then it'll store the current cursor position and label into the g_label
**	linked list.
*/

void		preprocess(void)
{
	char		*line;

	lseek_temp(0);
	while (get_temp_line(&line))
	{
		if (identify_line(line) == 1)
			preprocess_line(line);
		else if (identify_line(line) == 4)
		{
			find_replace(':', '\0', line);
			add_label(line, g_cursor_preprocess);
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
