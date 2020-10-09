/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flolefeb <flolefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 16:50:35 by flolefeb          #+#    #+#             */
/*   Updated: 2020/10/09 16:57:05 by flolefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_H
# define KEYCODE_H

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1
# define KEYRELEASEMASK 10
# define STRUCTURENOTIFYMASK 10001

#endif

#ifdef __linux__

# define KEY_ESCAPE 65307
# define KEY_A 113
# define KEY_D 100
# define KEY_S 115
# define KEY_W 122
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

#else

# define KEY_ESCAPE 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_S 1
# define KEY_W 13
# define KEY_A 0
# define KEY_D 2

#endif
