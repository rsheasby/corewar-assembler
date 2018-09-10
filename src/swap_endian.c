/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 08:43:30 by rsheasby          #+#    #+#             */
/*   Updated: 2017/09/09 13:53:48 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>

/*
**	This function will convert a small-endian long to a big-endian long
**	(or visa versa). NOTE: the BYTES are swapped around. NOT the BITS.
**	0x12345678 becomes 0x78563412.
*/

unsigned long	swap_endian_long(unsigned long num)
{
	int	result;

	result = ((num >> 24) & 0x000000ff) | ((num << 8) & 0x00ff0000) |
			((num >> 8) & 0x0000ff00) | ((num << 24) & 0xff000000);
	return (result);
}

/*
**	This function will convert a small-endian short to a big-endian short
**	(or visa versa). NOTE: the BYTES are swapped around. NOT the BITS.
**	0x1234 becomes 0x3412.
*/

unsigned short	swap_endian_short(unsigned short num)
{
	return ((num << 8) | (num >> 8));
}
