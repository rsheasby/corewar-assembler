/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 21:16:13 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:58:30 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assembler/include/asm.h>
#include <libft/libft.h>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		initialize(argv[1]);
		preprocess();
		process();
		write_file(g_filename_out);
		cleanup();
	}
	else
		ft_putendl("ERROR: Invalid argument[s]...");
	return (0);
}
