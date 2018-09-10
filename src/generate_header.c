/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 07:14:44 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:56:01 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>
#include <stdlib.h>

/*
**	This function will generate a header from the information provided.
**	It will verify all information is within the limits, and if so,
**	will allocate a space in memory for the data and populate it with the
**	information provided, and finally return a pointer to the header.
*/

t_header	*generate_header(unsigned int magic, char *name, unsigned long size,
	char *comment)
{
	t_header	*header;

	if (ft_strlen(name) > PROG_NAME_LENGTH ||
	ft_strlen(comment) > COMMENT_LENGTH ||
	size > CHAMP_MAX_SIZE)
		header = 0;
	else
	{
		header = (t_header *)ft_memalloc(sizeof(t_header));
		header->magic = swap_endian_long(magic);
		ft_strcpy(header->prog_name, name);
		header->prog_size = swap_endian_long(size);
		ft_strcpy(header->comment, comment);
	}
	return (header);
}
