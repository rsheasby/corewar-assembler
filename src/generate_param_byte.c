/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_param_byte.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:34:59 by rsheasby          #+#    #+#             */
/*   Updated: 2017/09/16 12:52:29 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <assembler/include/asm.h>

/*
**	This will check the first character of a parameter to determine it's type.
*/

static char	parse_param(char *word)
{
	if (word[0] == 'r')
		return (0b01010100);
	else if (word[0] == DIRECT_CHAR)
		return (0b10101000);
	else
		return (0b11111100);
}

/*
**	This function will take a line and generate the param-byte for it.
**	"sti r1, 2, %3" will return 0b 01 11 10 00.
*/

char		generate_param_byte(char *line)
{
	char	**words;
	int		len;
	char	result;

	words = ft_strsplit(line, ' ');
	len = 0;
	while (words[len])
		len++;
	if (len >= 2)
	{
		result = 0b11000000 & parse_param(words[1]);
		if (len >= 3)
		{
			result |= 0b00110000 & parse_param(words[2]);
			if (len >= 4)
				result |= 0b00001100 & parse_param(words[3]);
		}
	}
	else
		result = 0b00000000;
	ft_strarrdel(&words);
	return (result);
}
