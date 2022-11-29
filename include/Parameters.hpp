/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parameters.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:20:46 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 22:50:59 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_HPP
# define PARAMETERS_HPP

# define LINES_PLAYER 5
# define COLS_PLAYER 5
# define LINES_GAME (12 * LINES_PLAYER)
# define COLS_GAME (24 * COLS_PLAYER)
# define LINES_UI 6
# define COLS_UI COLS_GAME + 8

# define COLOR_BACKGROUND1 11
# define COLOR_BACKGROUND2 12
# define COLOR_BACKGROUND3 13
# define COLOR_BACKGROUND4 14
# define COLOR_BACKGROUND5 15
# define COLOR_BACKGROUND6 16
# define COLOR_BROWN1 21
# define COLOR_BROWN2 22
# define COLOR_BROWN3 23
# define COLOR_BROWN4 24
# define COLOR_GREY 30

# define PAIR_BACKGROUND1 11
# define PAIR_BACKGROUND2 12
# define PAIR_BACKGROUND3 13
# define PAIR_BACKGROUND4 14
# define PAIR_BACKGROUND5 15
# define PAIR_BACKGROUND6 16
# define PAIR_BROWN1 21
# define PAIR_BROWN2 22
# define PAIR_BROWN3 23
# define PAIR_BROWN4 24
# define PAIR_BACKGROUND_WHITE 31
# define PAIR_BACKGROUND_GREY 32
# define PAIR_BLUE 40
# define PAIR_RED 41
# define PAIR_LIGHT_BROWN 42
# define PAIR_MAGENTA 43

# define RAY_LENGTH 5

# define SECONDS_TO_SPAWN_BOSS 60

# define DEFAULT_LIVES 3
# define DEFAULT_CANON_POWER 0
# define DEFAULT_SHIELD_POWER 0

#endif
