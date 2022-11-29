/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:21:08 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 17:59:39 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "Ray.hpp"
#include "Parameters.hpp"

// Constructors
Ray::Ray()
{
	_x = 0;
	_y = 0;
	_vy = 0;
}

Ray::Ray(const Ray &copy)
{
	*this = copy;
}

Ray::Ray(int x, int y, int vx, int vy)
{
	_x = x;
	_y = y;
	_vx = vx;
	_vy = vy;
	_dir = 0 * (_vx < 0 && _vy == 0)
		+ 1 * (_vx < 0 && _vy > 0)
		+ 2 * (_vx == 0 && _vy > 0)
		+ 3 * (_vx > 0 && _vy > 0)
		+ 4 * (_vx > 0 && _vy == 0)
		+ 5 * (_vx > 0 && _vy < 0)
		+ 6 * (_vx == 0 && _vy < 0)
		+ 7 * (_vx < 0 && _vy < 0);
	this->computeDisplay();
	this->computeDisplayAttr();
}

extern WINDOW	*windowGame;

void	Ray::computeDisplay(void)
{
	std::string display[8] = {
		"||||||||||",
		"**********",
		"----------",
		"\\\\\\\\\\\\\\\\\\\\",
		"||||||||||",
		"//////////",
		"----------",
		"**********",
	};
	_display = display[_dir];
}

void	Ray::computeDisplayAttr(void)
{
	int	b = COLOR_PAIR(PAIR_BLUE);
	int	r = COLOR_PAIR(PAIR_RED);
	int l = COLOR_PAIR(PAIR_LIGHT_BROWN);
	std::vector<int> displayAttr[8] = {
		{l, 0, l, 0, l, 0, l, 0, l, 0},
		{l, 0, l, 0, l, 0, l, 0, l, 0},
		{r, b, r, b, r, b, r, b, r, b},
		{r, b, r, b, r, b, r, b, r, b},
		{r, b, r, b, r, b, r, b, r, b},
		{r, b, r, b, r, b, r, b, r, b},
		{r, b, r, b, r, b, r, b, r, b},
		{l, 0, l, 0, l, 0, l, 0, l, 0},
	};
	_displayAttr = displayAttr[_dir];
}


// Destructor
Ray::~Ray()
{
}


// Operators
Ray & Ray::operator=(const Ray &assign)
{
	_x = assign.getX();
	_y = assign.getY();
	_vx = assign.getVx();
	_vy = assign.getVy();
	_display = assign.getDisplay();
	_displayAttr = assign.getDisplayAttr();
	return *this;
}


// Getters / Setters
int Ray::getX() const
{
	return _x;
}
int Ray::getY() const
{
	return _y;
}
int Ray::getVx() const
{
	return _vx;
}
int Ray::getVy() const
{
	return _vy;
}
std::string	Ray::getDisplay(void) const
{
	return (_display);
}
std::vector<int>	Ray::getDisplayAttr(void) const
{
	return (_displayAttr);
}


//Methods
void Ray::update()
{
	_x += _vx;
	_y += _vy;
}

void Ray::display(WINDOW *w) const
{
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		if(_x + (i * _vx) >= 0 && _x + (i * _vx) < LINES_GAME
			&& _y + (i * _vy) >= 0 && _y + (i * _vy) < COLS_GAME)
		{
			wattron(w, _displayAttr[i]);
			mvwaddch(w, _x + (i * _vx), _y + (i * _vy), _display[i]);
			wattroff(w, _displayAttr[i]);
		}
	}
}

bool Ray::intersect(Ennemy &ent) const
{
	std::vector<std::pair<int, int>> positions = std::vector<std::pair<int, int>>();
	for(int i = ent.getPosX(); i <= ent.getPosX() + 3; i ++)
	{
		for(int j = ent.getPosY(); j <= ent.getPosY() + 2; j++)
		{
			positions.push_back(std::make_pair(i, j));
		}
	}
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		std::pair<int, int> pos = std::make_pair(_x + (i * _vx), _y + (i * _vy));
		if(std::find(positions.begin(), positions.end(), pos) != positions.end())
			return true;
	}
	return false;
}

bool Ray::intersect(Player &ent) const
{
	std::vector<std::pair<int, int>> positions = std::vector<std::pair<int, int>>();
	for(int i = ent.getPosX(); i <= ent.getPosX() + 3; i ++)
	{
		for(int j = ent.getPosY(); j <= ent.getPosY() + 2; j++)
		{
			positions.push_back(std::make_pair(i, j));
		}
	}
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		std::pair<int, int> pos = std::make_pair(_x + (i * _vx), _y + (i * _vy));
		if(std::find(positions.begin(), positions.end(), pos) != positions.end())
			return true;
	}
	return false;
}

int Ray::intersect(Boss &ent) const
{
	std::vector<std::pair<int, int>> positions = std::vector<std::pair<int, int>>();
	for(int i = ent.getY(); i <= ent.getY() + 4; i ++)
	{
		positions.push_back(std::make_pair(ent.getX() + 8, i));
	}
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		std::pair<int, int> pos = std::make_pair(_x + (i * _vx), _y + (i * _vy));
		if(std::find(positions.begin(), positions.end(), pos) != positions.end())
			return 0;
	}
	positions.clear();
	for(int i = ent.getY() + 5; i <= ent.getY() + 9; i ++)
	{
		positions.push_back(std::make_pair(ent.getX() + 8, i));
	}
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		std::pair<int, int> pos = std::make_pair(_x + (i * _vx), _y + (i * _vy));
		if(std::find(positions.begin(), positions.end(), pos) != positions.end())
			return 1;
	}
	positions.clear();
	for(int i = ent.getY() + 10; i <= ent.getY() + 14; i ++)
	{
		positions.push_back(std::make_pair(ent.getX() + 8, i));
	}
	for(int i = 0; i < RAY_LENGTH; i++)
	{
		std::pair<int, int> pos = std::make_pair(_x + (i * _vx), _y + (i * _vy));
		if(std::find(positions.begin(), positions.end(), pos) != positions.end())
			return 2;
	}
	return -1;
}

bool Ray::exist(void) const
{
	if(_x < 0 || _x >= LINES_GAME + RAY_LENGTH || _y < 0 || _y >= COLS_GAME + RAY_LENGTH)
		return false;
	return true;
}
