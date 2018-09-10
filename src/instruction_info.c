/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 17:04:18 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:58:20 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>

/*
**	This function will return the opcode for a word.
*/

char	instruction_opcode(char *instruction)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab[i].opcode);
		i++;
	}
	return (0);
}

/*
**	This function will return whether or not the instruction has a param_byte.
*/

_Bool	instruction_param_byte(char *instruction)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab[i].param_byte);
		i++;
	}
	return (-1);
}

/*
**	This function will return whether or not the instruction uses indices.
*/

_Bool	instruction_index(char *instruction)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab[i].index);
		i++;
	}
	return (-1);
}

/*
**	This function will return the parameters count for an instruction.
*/

short	instruction_params_num(char *instruction)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < 16)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab[i].args_num);
		i++;
	}
	return (-1);
}

/*
**	This function will return the array of argument types for an instruction.
*/

short	*instruction_params_type(char *instruction)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < 16)
	{
		if (!ft_strcmp(instruction, g_op_tab[i].name))
			return (g_op_tab[i].args_type);
		i++;
	}
	return (0);
}
