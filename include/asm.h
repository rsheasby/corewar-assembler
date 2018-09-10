/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsheasby <rsheasby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 12:06:13 by rsheasby          #+#    #+#             */
/*   Updated: 2017/10/01 14:56:05 by rsheasby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
**** Includes ****
*/

# include <op/op.h>

/*
**** Struct definitions. ****
*/

typedef struct	s_label
{
	char			*label;
	unsigned int	cursor;
	struct s_label	*next;
}				t_label;

/*
**** Globals. ****
*/

char			g_prog_name[PROG_NAME_LENGTH + 1];
char			g_prog_comment[COMMENT_LENGTH + 1];
char			*g_filename_in;
char			*g_filename_out;
int				g_cursor_preprocess;
unsigned int	g_cursor_out;
unsigned int	g_o_cursor_out;
t_label			*g_labels;
unsigned int	g_cursor_in;
unsigned int	g_cursor_out;
char			*g_temp_in;
char			g_temp_out[CHAMP_MAX_SIZE];

/*
**** Function prototypes ****
*/

char			instruction_opcode(char *instruction);
void			read_error(char *filename);
_Bool			instruction_param_byte(char *instruction);
_Bool			instruction_index(char *instruction);
short			instruction_params_num(char *instruction);
short			*instruction_params_type(char *instruction);
t_header		*generate_header(unsigned int magic, char *name,
		unsigned long size, char *comment);
char			generate_param_byte(char *line);
unsigned long	swap_endian_long(unsigned long num);
unsigned short	swap_endian_short(unsigned short num);
char			*format_line(char *line);
int				identify_line(char *line);
void			initialize(char *filename);
void			read_file(char *filename);
int				get_temp_line(char **str);
void			cleanup(void);
void			read_name(char *line);
void			read_comment(char *line);
void			write_out(char *data, unsigned int len);
_Bool			write_file(char *filename);
void			process(void);
void			preprocess(void);
void			find_replace(char find, char replace, char *string);
void			add_label(char *label, unsigned int cursor);
int				search_label(char *label);
void			lseek_temp(unsigned int	cursor);
void			delete_labels(t_label *label);
void			check_error(int ln, char *line);
void			preprocess_filename(char *filename);
void			gen_filename(void);
_Bool			verify_param(char *param);

#endif
