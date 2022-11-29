/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BackgroundDot.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:44:19 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 05:16:39 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "BackgroundDot.hpp"
#include "Parameters.hpp"

BackgroundDot::BackgroundDot(BackgroundDot const &src)
{
    *this = src;
}

BackgroundDot::BackgroundDot(void)
{
	_x = 0;
	_y = rand() % COLS_GAME;
	_iMax = rand() % 60 + 60;
	_i = rand() % _iMax;
	_c = ".*"[rand() % 2];
}

BackgroundDot::BackgroundDot(int x)
{
	_x = x;
	_y = rand() % COLS_GAME;
	_iMax = rand() % 60 + 60;
	_i = rand() % _iMax;
	_c = ".*"[rand() % 2];
}

BackgroundDot::~BackgroundDot(void)
{
}

BackgroundDot&   BackgroundDot::operator=(BackgroundDot const &rhs)
{
	_x = rhs.getX();
	_y = rhs.getY();
	_i = rhs.getI();
	_iMax = rhs.getIMax();
	_c = rhs.getC();
    return (*this);
}

bool	BackgroundDot::isOutOfScreen(void) const
{
	return (_x >= LINES_GAME);
}

void	BackgroundDot::display(WINDOW *w) const
{
	wattron(w, COLOR_PAIR((_iMax - 60) / 10 + 11));
	mvwaddch(w, _x, _y, _c);
	wattroff(w, COLOR_PAIR((_iMax - 60) / 10 + 11));
}

void	BackgroundDot::update(void)
{
	_i++;
	if (_i >= _iMax)
	{
		_i = 0;
		_x++;
	}
}
