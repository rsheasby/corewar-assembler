/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 20:52:40 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 13:39:20 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>
#include <stdlib.h>

/*
**	Fairly generic linked list adder. Nothing to see here.
*/

void	add_label(char *label, unsigned int cursor)
{
	t_label	*end;

	if (!g_labels)
	{
		g_labels = (t_label *)ft_memalloc(sizeof(t_label));
		g_labels->label = ft_strdup(label);
		g_labels->cursor = cursor;
		g_labels->next = 0;
	}
	else
	{
		end = g_labels;
		while (end->next)
			end = end->next;
		end->next = (t_label *)ft_memalloc(sizeof(t_label));
		end->next->label = ft_strdup(label);
		end->next->cursor = cursor;
		end->next->next = 0;
	}
}

/*
**	Looks for matching label in linked list and returns the cursor. If no label
**	is found, then it outputs an error and safely exits. Unfortunately, as this
**	must happen during the processing stage, the line number can't be output to
**	the command line.
*/

int		search_label(char *label)
{
	t_label	*result;

	if (g_labels)
	{
		result = g_labels;
		while (result->next && ft_strcmp(label, result->label))
			result = result->next;
		if (!ft_strcmp(label, result->label))
			return (result->cursor);
	}
	ft_putstr("Label \"");
	ft_putstr(label);
	ft_putendl("\" not found.");
	cleanup();
	exit(EXIT_FAILURE);
	return (-1);
}

/*
**	This function deletes all the labels nice and quick using recursion.
*/

void	delete_labels(t_label *label)
{
	if (label)
	{
		if (label->next)
			delete_labels(label->next);
		ft_strdel(&label->label);
		ft_memdel((void **)&label);
	}
}
