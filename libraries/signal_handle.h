/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 00:59:25 by mde-arpe          #+#    #+#             */
/*   Updated: 2023/08/16 01:25:34 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLE_H
# define SIGNAL_HANDLE_H

# include <signal.h>
# include <unistd.h>

void	sig_handler_interactive(int signum);
void	sig_handler_here_doc(int signum);
void	sig_setter(sig_t func);

#endif