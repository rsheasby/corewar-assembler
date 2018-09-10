/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 10:40:45 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 13:03:15 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <assembler/include/asm.h>

/*
**	This will check if a string is a valid label
*/

static _Bool	is_label(char *word)
{
	unsigned long	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == LABEL_CHAR && i == ft_strlen(word) - 1)
			return (1);
		if (!ft_strchr(LABEL_CHARS, word[i]))
			return (0);
		i++;
	}
	return (0);
}

/*
**	The following functions will identify what type of line we are looking at.
**	0.	Invalid Instruction / Garbage.
**	1.	Regular Instruction.
**	2.	Name Definition.
**	3.	Comment Definition.
**	4.	Label.
**	5.	Label + Instruction.
**	6.	Label + Garbage.
**	7.	Invalid Label (Using disallowed alphabet).
**	8.	Blank Line.
**
**	(get_val is just 25 line limit evasion)
*/

static int		get_val(char **words)
{
	if (instruction_opcode(words[0]))
		return (1);
	else if (!ft_strcmp(words[0], NAME_CMD_STRING))
		return (2);
	else if (!ft_strcmp(words[0], COMMENT_CMD_STRING))
		return (3);
	else if (is_label(words[0]) && !words[1])
		return (4);
	else if (is_label(words[0]) && instruction_opcode(words[1]))
		return (5);
	else if (is_label(words[0]) && words[1])
		return (6);
	else if (words[0][ft_strlen(words[0]) - 1] == LABEL_CHAR)
		return (7);
	else
		return (0);
}

int				identify_line(char *line)
{
	char	**words;
	char	*temp;
	int		val;

	temp = ft_strdup(line);
	find_replace('\n', ' ', temp);
	words = ft_strsplit(temp, ' ');
	if (!temp[0] || words[0][0] == COMMENT_CHAR)
		val = 8;
	else
		val = get_val(words);
	ft_strarrdel(&words);
	ft_strdel(&temp);
	return (val);
}
