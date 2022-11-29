/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Alien.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:13:51 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 23:18:28 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Alien.hpp"
#include "Parameters.hpp"

Alien::Alien(Alien const &src)
{
    *this = src;
}

Alien::Alien(int x, int y, int t): Ennemy(x, y, true)
{
	int	b;

    _framesToFall = (rand() % 5 + 23) * 120 / (t + 120);
    _framesFromLastFall = 0;
    _type = "alien";
    _display = std::vector<std::string>();
	switch (rand() % 3)
	{
	case 0:
		_display.push_back("/---\\");
		_display.push_back("| * |");
		_display.push_back("\\---/");
		break;
	case 1:
		_display.push_back(",~~~,");
		_display.push_back(": o :");
		_display.push_back("'~~~'");
		break;
	case 2:
		_display.push_back(".....");
		_display.push_back("| $ |");
		_display.push_back(".....");
		break;
	}
    _framesToShoot = (rand() % 10 + 170) * 240 / (t + 240);
    _framesFromLastShoot = 1;
    _displayAttr = std::vector<std::vector<int>>();
	b = COLOR_PAIR(PAIR_BLUE);
    _displayAttr.push_back(std::vector<int> {b, 0, 0, 0, b});
    _displayAttr.push_back(std::vector<int> {0, 0, b, 0, 0});
    _displayAttr.push_back(std::vector<int> {b, 0, 0, 0, b});
}

Alien&   Alien::operator=(Alien const &rhs)
{
	Ennemy::operator=(rhs);
    return (*this);
}
