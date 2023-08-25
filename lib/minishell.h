/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia-ma <lucia-ma@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 03:48:31 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/23 18:14:46 by lucia-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef MALLOC_DEBUG
#  include "malloc_debug.h"
# endif

# include "lexer.h"
# include "parser.h"
# include "signal_handle.h"
# include "exit_status.h"
# include "libft.h"
# include "builtins.h"
# include "expander.h"
# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

int	g_exit_status;

#endif