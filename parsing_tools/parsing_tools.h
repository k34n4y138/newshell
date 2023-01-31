/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:18:16 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/31 16:20:27 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H
# include <stdbool.h>

typedef enum e_output_type
{
	C_OUT_NONE,
	C_OUT_PIPE,
	C_OUT_FILE,
	C_OUT_APPEND
}	t_output_type;

typedef enum e_input_type
{
	C_IN_NONE,
	C_IN_PIPE,
	C_IN_FILE,
	C_IN_HEREDOC
}	t_input_type;

typedef enum e_tokentype
{
	TK_NONE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_TASKSPLITTER,
	TK_DOUBLEQ,
	TK_SINGLEQ,
	TK_VARKEY,
	TK_ASSIGN,
	TK_ARG
	
}	t_lexitoken_type;

typedef struct s_lextoken
{
	char				*token;
	t_lexitoken_type	type;
	bool				space_after;
	struct s_lextoken	*prev;
	struct s_lextoken	*next;
}	t_lexitoken;

typedef enum e_taskrelation
{
	TREL_NONE,
	TREL_AND,
	TREL_OR,
	TREL_PIPE
}	t_taskrelation;

typedef struct s_exectask
{
	char				*rawtask;
	t_lexitoken			*rawtoken;

	char				*command;
	char				**args;
	t_input_type		input_type;
	union
	{
		char			*heredoc_del;
		int				in_pipe;
		char			*input_file;

	};
	t_output_type		output_type;
	union
	{
		char			*output_file;
		int				out_pipe;
	};
	
	t_taskrelation		taskrelation;
	
	struct s_exectask		*next;
	struct s_exectask		*prev;
}						t_exectask;

typedef struct s__prs
{
	int		start_idx;
	int		end_idx;
	char	*task;
	int		tasksplitter_type;	
}		t_parsingtask;
char	*tokenize_till_quote(char	*line, char deli, int *to_append, int withquote);
t_exectask	*parse_commandline(char *line);
#endif