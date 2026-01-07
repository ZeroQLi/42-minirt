/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanasser <nanasser@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:04:01 by nanasser          #+#    #+#             */
/*   Updated: 2026/01/05 01:04:01 by nanasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* Colors ✨ */
/* Pls use appropriately */
# define RED   "\033[0;31m"
# define BRED  "\033[1;31m"
# define YELLOW  "\033[0;33m"
# define BYELLOW "\033[1;33m"
# define GREEN   "\033[0;32m"
# define BGREEN  "\033[1;32m"
# define BLUE    "\033[0;34m"
# define BBLUE   "\033[1;34m"
# define MAGENTA "\033[0;35m"
# define BMAGENTA "\033[1;35m"
# define CYAN    "\033[0;36m"
# define BCYAN   "\033[1;36m"
# define WHITE   "\033[0;37m"
# define BWHITE  "\033[1;37m"
# define RESET "\033[0m"

// yes.
# define YES 1
# define NO 0

// error strings
# define ARGUMENT_ERROR RED"Argument format: ./minirt [scene_name].rt"RESET
# define INVALID_FILE RED"Invalid file! Make sure it exists and has a .rt \
extension!"RESET

#endif