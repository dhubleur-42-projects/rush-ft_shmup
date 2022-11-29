/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:32:25 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 05:25:46 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.hpp"
#include "Parameters.hpp"

//Constructors
Entity::Entity(void) : _x(0), _y(0)
{
}

Entity::Entity(int x, int y) : _x(x), _y(y)
{
}

Entity::Entity(Entity const &src)
{
	*this = src;
}


//Destructor
Entity::~Entity(void)
{
}


//Operators
Entity& Entity::operator=(Entity const &rhs)
{
	_x = rhs.getPosX();
	_y = rhs.getPosY();
	_display = rhs.getDisplay();
	_displayAttr = rhs.getDisplayAttr();
	return (*this);
}


//Getters / Setters
int		Entity::getPosX(void) const
{
	return (_x);
}
int		Entity::getPosY(void) const
{
	return (_y);
}
std::vector<std::string>	Entity::getDisplay(void) const
{
	return (_display);
}
std::vector<std::vector<int>>	Entity::getDisplayAttr(void) const
{
	return (_displayAttr);
}
void	Entity::setPos(int x, int y)
{
	_x = x;
	_y = y;
}
void	Entity::setDisplay(std::vector<std::string> display)
{
	_display = display;
}
void	Entity::setDisplayAttr(std::vector<std::vector<int>> displayAttr)
{
	_displayAttr = displayAttr;
}


//Methods
void	Entity::display(WINDOW *w) const
{
	for(int i = 0; i < (int) _display.size(); i++)
	{
		if(_x + i < 0 || _x + i >= LINES_GAME)
			continue ;
		for (int j = 0; j < (int) _display.at(i).size(); j++)
		{
			if (_display.at(i).at(j) == ' ')
				continue;
			if (_displayAttr.at(i).at(j) != 0)
				wattron(w, _displayAttr.at(i).at(j));
			mvwaddch(w, _x + i, _y + j, _display.at(i).at(j));
			if (_displayAttr.at(i).at(j) != 0)
				wattroff(w, _displayAttr.at(i).at(j));
		}
	}
}
