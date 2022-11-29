/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:44:19 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 05:12:55 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Background.hpp"
#include "Parameters.hpp"

Background::Background(Background const &src)
{
    *this = src;
}

Background::Background(void)
{
	_dots = std::vector<BackgroundDot>();
	for (int i = 0; i < LINES_GAME; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			while (rand() % 8 == 0)
			{
				BackgroundDot newDot = BackgroundDot(i);
				_dots.push_back(newDot);
			}
		}
	}
}

Background::~Background(void)
{
}

Background&   Background::operator=(Background const &rhs)
{
	_dots = rhs.getDots();
	return (*this);
}

std::vector<BackgroundDot>	Background::getDots(void) const
{
	return (_dots);
}

void	Background::display(WINDOW *w) const
{
	werase(w);
	for (BackgroundDot dot : _dots)
		dot.display(w);
}

void	Background::update(void)
{
	for (std::vector<BackgroundDot>::iterator it = _dots.begin(); it != _dots.end(); ++it)
	{
		BackgroundDot &dot = *it;
		dot.update();
		if (dot.isOutOfScreen())
			_dots.erase(it--);
	}
	while (rand() % 8 == 0)
	{
		BackgroundDot newDot = BackgroundDot();
		_dots.push_back(newDot);
	}
}
