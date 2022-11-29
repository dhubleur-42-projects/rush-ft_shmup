/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rock.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:13:51 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 23:17:38 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parameters.hpp"
#include "Rock.hpp"

Rock::Rock(Rock const &src)
{
    *this = src;
}

Rock::Rock(int x, int y, int t): Ennemy(x, y, false)
{
    _framesToFall = (rand() % 3 + 4) * 120 / (t + 120);
    _framesFromLastFall = 0;
    _type = "rock";
    _display = std::vector<std::string>();
	switch (rand() % 5)
	{
	case 0:
		_display.push_back(".www.");
		_display.push_back("&###k");
		_display.push_back("'mmm'");
		break;
	case 1:
		_display.push_back(" www ");
		_display.push_back("&m##k");
		_display.push_back(" 'mmk");
		break;
	case 2:
		_display.push_back(" .wwk");
		_display.push_back("&###k");
		_display.push_back("'mmm'");
		break;
	case 3:
		_display.push_back(" .xx ");
		_display.push_back(" &Hhk");
		_display.push_back(" vv; ");
		break;
	case 4:
		_display.push_back("  _  ");
		_display.push_back(" .#k ");
		_display.push_back("  mm ");
		break;
	default:
		break;
	}
    _framesToShoot = 0;
    _framesFromLastShoot = 0;
    _displayAttr = std::vector<std::vector<int>>();
    _displayAttr.push_back(std::vector<int> {0, 0, 0, 0, 0});
    _displayAttr.push_back(std::vector<int> {0, 0, 0, 0, 0});
    _displayAttr.push_back(std::vector<int> {0, 0, 0, 0, 0});
	std::vector<int>	m = std::vector<int> {
		COLOR_PAIR(PAIR_BROWN1),
		COLOR_PAIR(PAIR_BROWN2),
		COLOR_PAIR(PAIR_BROWN3),
		COLOR_PAIR(PAIR_BROWN4)};
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			_displayAttr[i][j] = m[rand() % 4];
}

Rock&   Rock::operator=(Rock const &rhs)
{
	Ennemy::operator=(rhs);
    return (*this);
}
