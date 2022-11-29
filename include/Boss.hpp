/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:27:05 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 21:48:59 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOSS_HPP
# define BOSS_HPP

# include <ncurses.h>
# include <vector>
# include <string>
# include "Boss.hpp"

class Ray;

class Boss
{
    public:
		//Constructors
		Boss(void);
		Boss(Boss const &src);

		//Destructor
		virtual ~Boss(void);

		//Operators
		Boss	&operator=(Boss const &rhs);

		//Getters / Setters
		int getX(void) const;
        int getY(void) const;
        int getDestX(void) const;
        int getDestY(void) const;
        int getCurrentCanon(void) const;
        int getCanonLife(int i) const;
        int getToMove(void) const;
        int getLastMove(void) const;
        int getFrameToShoot(void) const;
        int getLastShoot(void) const;
        int getAfterDeath(void) const;
		std::vector<std::string>	getDisplay(void) const;

		//Methods
        void    update(void);
        void    display(WINDOW *w) const;
		bool    isDead(void) const;
        bool    intersect(Ray const &ray);
        void    setDisplayAttributs();

	protected:
		int _x;
        int _y;
        int _destX;
        int _destY;
        int _canonsLife[3];
        int _currentCanon;
        int _toMove;
        int _lastMove;
        int _frameToShoot;
        int _lastShoot;
        int _afterDeath;
		std::vector<std::string>		_display;
        std::vector<std::vector<int>>   _displayAttributes;
        void pushCanon(bool selected, int life);
};

#endif
