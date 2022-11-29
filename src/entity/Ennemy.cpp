/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ennemy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:32:25 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 15:43:09 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ennemy.hpp"
#include "Parameters.hpp"

//Constructors
Ennemy::Ennemy(void) : Ennemy(0, 0, false)
{
}

Ennemy::Ennemy(int x, int y, bool killable): Entity(x, y), _killable(killable)
{
}

Ennemy::Ennemy(Ennemy const &src)
{
	*this = src;
}


//Destructor
Ennemy::~Ennemy(void)
{
}


//Operators
Ennemy& Ennemy::operator=(Ennemy const &rhs)
{
	Entity::operator=(rhs);
	_framesToFall = rhs.getFramesToFall();
	_framesFromLastFall = rhs.getFramesFromLastFall();
	_killable = rhs.isKillable();
	_type = rhs.getType();
	_framesFromLastShoot = rhs.getFramesFromLastShoot();
	_framesToShoot = rhs.getFramesToShoot();
	return (*this);
}


//Getters / Setters
int    Ennemy::getFramesToFall(void) const
{
    return (_framesToFall);
}
int    Ennemy::getFramesFromLastFall(void) const
{
    return (_framesFromLastFall);
}
bool Ennemy::isKillable(void) const
{
	return (_killable);
}
std::string Ennemy::getType(void) const
{
	return (_type);
}
int    Ennemy::getFramesToShoot(void) const
{
	return (_framesToShoot);
}
int    Ennemy::getFramesFromLastShoot(void) const
{
	return (_framesFromLastShoot);
}

void    Ennemy::update(void)
{
    if(_framesFromLastFall >= _framesToFall)
    {
        _x++;
        _framesFromLastFall = 0;
    }
    else
	{
        ++_framesFromLastFall;
	}
	if(_framesToShoot > 0)
	{
		if(_framesFromLastShoot >= _framesToShoot)
			_framesFromLastShoot = 0;
		else
			++_framesFromLastShoot;
	}
	if (this->getType() == "alien")
	{
		if (_framesFromLastShoot == 0)
		{
			_displayAttr[0][0] = COLOR_PAIR(PAIR_BLUE);
			_displayAttr[0][4] = COLOR_PAIR(PAIR_BLUE);
			_displayAttr[1][2] = COLOR_PAIR(PAIR_BLUE);
			_displayAttr[2][0] = COLOR_PAIR(PAIR_BLUE);
			_displayAttr[2][4] = COLOR_PAIR(PAIR_BLUE);
		}
		if (_framesFromLastShoot == _framesToShoot - 30)
		{
			_displayAttr[0][0] = COLOR_PAIR(PAIR_RED);
			_displayAttr[0][4] = COLOR_PAIR(PAIR_RED);
			_displayAttr[2][0] = COLOR_PAIR(PAIR_RED);
			_displayAttr[2][4] = COLOR_PAIR(PAIR_RED);
		}
		if (_framesFromLastShoot == _framesToShoot - 10)
		{
			_displayAttr[1][2] = COLOR_PAIR(PAIR_RED);
		}
	}
}

//Methods
bool	Ennemy::exist(void) const
{
	int max = _display.size();
	if(_x - max > LINES_GAME)
		return false;
	return true;
}

bool Ennemy::intersect(Player &player) const
{
	int max = _display.size();
	for(int i = 0; i < max; i++)
	{
		if(_x + i == player.getPosX() && _y == player.getPosY())
			return true;
	}
	return false;
}
