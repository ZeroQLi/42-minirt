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

# define EPSILON 0.00001

# define WIN_WIDTH 1366
# define WIN_HEIGHT 768

// yes.
# define YES 1
# define NO 0

// error strings
# define ARG_ERROR "\033[0;31mArgument format: ./minirt [scene_name].rt\033[0m"
# define INVALID_FILE "\033[0;31mInvalid file! Make sure it exists and has a \
.rt extension!\033[0m"
# define MULTIPLE_AMBIENT_ERR "\033[0;31mcan't be too edgy now. There must only\
 be 1 instance of ambient.\033[0m"
# define MULTIPLE_CAMERA_ERR "\033[1;31mA\033[1;36mC\033[0;31m ain't paid \
enough to catch you aura farming off-screen. There must only be 1 instance of a\
 camera.\033[0m"
# define MULTIPLE_LIGHT_ERR "\033[0;31mSowwy, no GPU drivers = fried air fryer.\
 There must only be 1 instance of light.\033[0m"
# define NO_LIGHTS "who took the light out of you? boi \033[1;37mTURN EM BACK \
ON\033[0m"

# define EPSILON 0.00001
#endif