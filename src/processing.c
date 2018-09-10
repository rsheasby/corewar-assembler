/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 08:58:51 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 13:55:45 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>

/*
**	This function will return the atoi of the parameter if it's a number, and if
**	it's a label, it'll lookup the label, and return the difference between the
**	label's cursor, and the origin_cursor(the cursor of the last successfully
**	processed instruction). This essentially converts the label into an offset.
*/

static int	read_nbr(char *param)
{
	int	i;

	i = 0;
	while (!(ft_isdigit(param[i]) || param[i] == '-') && param[i])
	{
		if (param[i] == ':')
			return (search_label(param + i + 1) - g_o_cursor_out);
		++i;
	}
	return (ft_atoi(param + i));
}

/*
**	This function writes an integer to the temp file in reverse(thereby
**	swap_endian isn't necessary). It writes only the last len bytes.
*/

static void	write_nbr(int nbr, int len)
{
	while (len--)
		write_out((char *)&nbr + len, 1);
}

/*
**	This function will translate one line of instruction to the bytecode, and
**	write it to the temp file. It does so by splitting the line into separate
**	words, looking up and writing the instruction opcode, if necessary, it
**	generates and writes the param byte, and then one by one writes the
**	parameters using write_nbr() based on it's type and whether or not the
**	instruction uses indices.
*/

static void	process_line(char *line)
{
	char	**words;
	char	instruction;
	char	param_byte;
	int		i;
	int		nbr;

	words = ft_strsplit(line, ' ');
	instruction = instruction_opcode(words[0]);
	param_byte = generate_param_byte(line);
	write_out(&instruction, sizeof(char));
	if (instruction_param_byte(words[0]) == 1)
		write_out(&param_byte, sizeof(char));
	i = 0;
	while (words[++i] && i <= 3)
	{
		nbr = read_nbr(words[i]);
		if (words[i][0] == 'r')
			write_nbr(nbr, 1);
		else if (words[i][0] == DIRECT_CHAR && !instruction_index(words[0]))
			write_nbr(nbr, 4);
		else
			write_nbr(nbr, 2);
	}
	ft_strarrdel(&words);
}

/*
**	This function will process the temp file line by line using process_line().
**	It only processes lines of type 1(instruction).
*/

void		process(void)
{
	char		*line;

	lseek_temp(0);
	while (get_temp_line(&line))
	{
		g_o_cursor_out = g_cursor_out;
		if (identify_line(line) == 1)
			process_line(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
