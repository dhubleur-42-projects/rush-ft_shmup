/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartMenu.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 12:56:55 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 13:21:23 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTMENU_HPP
# define STARTMENU_HPP

# include <ncurses.h>

class StartMenu
{
    public:
        StartMenu(void);
        ~StartMenu(void);
        void	display(WINDOW *screen) const;
		void	handleInput(WINDOW *screen);

        bool    isEnded(void)  const;
        bool    isKilled(void)  const;

    private:
        int    _ended;
};

#endif