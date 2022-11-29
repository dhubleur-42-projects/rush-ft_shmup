/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EndMenu.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:56:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 14:03:42 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDMENU_HPP
# define ENDMENU_HPP

# include <ncurses.h>
# include <chrono>

class EndMenu
{
    public:
        EndMenu(int elapsed_time, int scores);
        ~EndMenu(void);
        void	display(WINDOW *screen) const;
		void	handleInput(WINDOW *screen);

        bool    isEnded(void)  const;

    private:
        int _elapsed_time;
        int _score;
        bool    _ended;
};

#endif