/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:30:14 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 23:03:10 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Boss.hpp"
#include "Parameters.hpp"
#include <string>
#include "Ray.hpp"

Boss::Boss():
        _x(-10),
        _y(10),
        _destX(2),
        _destY(-1),
        _currentCanon(-1),
        _toMove(15),
        _lastMove(1),
        _frameToShoot(50),
        _lastShoot(360),
        _afterDeath(0)
{
    _canonsLife[0] = 3;
    _canonsLife[1] = 3;
    _canonsLife[2] = 3;
	_display = std::vector<std::string>();
	switch (rand() % 4) {
	case 0:
		_display.push_back(std::string("   __     __   "));
		_display.push_back(std::string(" _|__|___|__|_ "));
		_display.push_back(std::string("|  ___   ___  |"));
		_display.push_back(std::string("| | o | | o | |"));
		_display.push_back(std::string("|  ---   ---  |"));
		_display.push_back(std::string("|  #########  |"));
		_display.push_back(std::string("/---\\/---\\/---\\"));
		_display.push_back(std::string("| * || * || * |"));
		_display.push_back(std::string("\\---/\\---/\\---/"));
		break ;
	case 1:
		_display.push_back(std::string("     _~-~_     "));
		_display.push_back(std::string("    (-._.-)    "));
		_display.push_back(std::string(".-(  `---'  )-."));
		_display.push_back(std::string("_\\ \\\\\\___/// /_"));
		_display.push_back(std::string("._.'/ \\ / \\`._,"));
		_display.push_back(std::string("  -----------  "));
		_display.push_back(std::string("/---\\/---\\/---\\"));
		_display.push_back(std::string("| * || * || * |"));
		_display.push_back(std::string("\\---/\\---/\\---/"));
		break ;
	case 2:
		_display.push_back(std::string("               "));
		_display.push_back(std::string("               "));
		_display.push_back(std::string("  /\\ \\  / /\\   "));
		_display.push_back(std::string(" //\\\\ .. //\\\\  "));
		_display.push_back(std::string(" //\\((  ))/\\\\  "));
		_display.push_back(std::string(" /  < `' >  \\  "));
		_display.push_back(std::string("/---\\/---\\/---\\"));
		_display.push_back(std::string("| * || * || * |"));
		_display.push_back(std::string("\\---/\\---/\\---/"));
		break ;
	case 3:
		_display.push_back(std::string("    ___        "));
		_display.push_back(std::string("  _/ ..\\       "));
		_display.push_back(std::string(" ( \\  0/__     "));
		_display.push_back(std::string("  \\    \\__)    "));
		_display.push_back(std::string("  /     \\      "));
		_display.push_back(std::string(" /      _\\     "));
		_display.push_back(std::string("/---\\/---\\/---\\"));
		_display.push_back(std::string("| * || * || * |"));
		_display.push_back(std::string("\\---/\\---/\\---/"));
		break ;
	default:
		break ;
	}
}

Boss::Boss(Boss const &src)
{
    *this = src;
}

Boss::~Boss(void)
{
}

Boss &Boss::operator=(Boss const &rhs)
{
    _x = rhs.getX();
    _y = rhs.getY();
	_display = rhs.getDisplay();
    _destX = rhs.getDestX();
    _destY = rhs.getDestY();
    _currentCanon = rhs.getCurrentCanon();
    _toMove = rhs.getToMove();
    _lastMove = rhs.getLastMove();
    _canonsLife[0] = rhs.getCanonLife(0);
    _canonsLife[1] = rhs.getCanonLife(1);
    _canonsLife[2] = rhs.getCanonLife(2);
    _frameToShoot = rhs.getFrameToShoot();
    _lastShoot = rhs.getLastShoot();
    _afterDeath = rhs.getAfterDeath();
    return (*this);
}

int Boss::getX(void) const
{
    return (_x);
}
int Boss::getY(void) const
{
    return (_y);
}
int Boss::getDestX(void) const
{
    return (_destX);
}
int Boss::getDestY(void) const
{
    return (_destY);
}
int Boss::getCurrentCanon(void) const
{
    return (_currentCanon);
}
int Boss::getCanonLife(int i) const
{
    return (_canonsLife[i]);
}
int Boss::getToMove(void) const
{
    return (_toMove);
}
int Boss::getLastMove(void) const
{
    return (_lastMove);
}
int Boss::getFrameToShoot(void) const
{
    return (_frameToShoot);
}
int Boss::getLastShoot(void) const
{
    return (_lastShoot);
}
int Boss::getAfterDeath(void) const
{
    return (_afterDeath);
}
std::vector<std::string>	Boss::getDisplay(void) const
{
	return (_display);
}

void    Boss::update(void)
{
    if(isDead())
        _afterDeath++;
    this->setDisplayAttributs();
    if(--_lastMove == 0)
    {
        _lastMove = _toMove;
        if(_destX != -1)
            _x += _destX > _x ? 1 : -1;
        if(_destY != -1)
            _y += _destY > _y ? 5 : -5;
        if((_destX == -1 || _x == _destX) && (_destY == -1 || _y == _destY))
        {
            if(_x == 2 && _y == 10)
            {
                _destX = 5, _destY = -1;
                if(_currentCanon == -1)
                    _currentCanon = rand()%3;
            }
            else if(_x == 5 && _y == 10)
                _destX = -1, _destY = COLS_GAME-20;
            else if(_x == 5 && _y == COLS_GAME-20)
                _destX = 2, _destY = -1;
            else if(_x == 2 && _y == COLS_GAME-20)
                _destX = -1, _destY = 10;
        }
    }
    if(--_lastShoot == 0)
    {
        _lastShoot = _frameToShoot;
    }
}
void    Boss::display(WINDOW *w) const
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            if (_displayAttributes.at(i).at(j) != 0)
				wattron(w, _displayAttributes.at(i).at(j));
            mvwaddch(w, _x + i, _y + j, _display[i][j]);
            if (_displayAttributes.at(i).at(j) != 0)
				wattroff(w, _displayAttributes.at(i).at(j));
        }
    }
}
bool    Boss::isDead(void) const
{
    for(int i = 0; i < 3; i++)
    {
        if (_canonsLife[i] > 0)
            return (false);
    }
    return (true);
}
bool    Boss::intersect(Ray const &ray)
{
    int inter = ray.intersect(*this);
    if(inter >= 0)
    {
        if(inter == _currentCanon)
        {
            if(--_canonsLife[_currentCanon] == 0)
            {
                _currentCanon ++;
                if(_currentCanon == 3)
                    _currentCanon = 0;
                if(_canonsLife[_currentCanon] == 0)
                {
                    _currentCanon = -1;
                    _destX = -1, _destY = -1;
                }
            }
        }
        return true;
    }
    return false;
}

void Boss::pushCanon(bool selected, int life)
{
    int b = COLOR_PAIR(PAIR_BLUE);
    int r = COLOR_PAIR(PAIR_RED);
    int o = COLOR_PAIR(PAIR_BROWN1);
    int w = 0;
    if(!selected && life == 3)
    {
        std::vector<int> line = {b, w, w, w, b};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {w, w, b, w, w};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {b, w, w, w, b};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
    else if(!selected && life == 0)
    {
        std::vector<int> line = {r, r, r, r, r};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {r, w, r, w, r};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {r, r, r, r, r};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
    else if(selected && life == 3)
    {
        std::vector<int> line = {o, o, o, o, o};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {o, w, b, w, o};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {o, o, o, o, o};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
    else if(selected && life == 2)
    {
        std::vector<int> line = {o, o, o, o, o};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {r, w, r, w, r};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {o, o, o, o, o};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
    else if(selected && life == 1)
    {
        std::vector<int> line = {o, o, o, o, o};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {r, w, r, w, r};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {r, r, r, r, r};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
    else if(selected && life == 0)
    {
        std::vector<int> line = {r, r, r, r, r};
        for(int i : line)
            _displayAttributes.at(6).push_back(i);
        line = {r, w, r, w, r};
        for(int i : line)
            _displayAttributes.at(7).push_back(i);
        line = {r, r, r, r, r};
        for(int i : line)
            _displayAttributes.at(8).push_back(i);
    }
}

void Boss::setDisplayAttributs(void)
{
	int b = COLOR_PAIR(PAIR_BLUE);
    int r = COLOR_PAIR(PAIR_RED);
    int w = 0;
    if(!isDead())
    {
		_displayAttributes = std::vector<std::vector<int>>();
        _displayAttributes.push_back(std::vector<int> {w, w, w, w, w, b, w, w, w, b, w, w, w, w, w});
        _displayAttributes.push_back(std::vector<int> {w, w, w, w, w, w, w, b, w, w, w, w, w, w, w});
        _displayAttributes.push_back(std::vector<int> {w, w, w, w, b, w, w, w, w, w, b, w, w, w, w});
        _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, w, w, w, w, w, b, w, w, w, b});
        _displayAttributes.push_back(std::vector<int> {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w});
        _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, b, w, w, w, b, b, w, w, w, b});
        
        _displayAttributes.push_back(std::vector<int>());
        _displayAttributes.push_back(std::vector<int>());
        _displayAttributes.push_back(std::vector<int>());

        pushCanon(_currentCanon == 0, _canonsLife[0]);
        pushCanon(_currentCanon == 1, _canonsLife[1]);
        pushCanon(_currentCanon == 2, _canonsLife[2]);

        /*if(_currentCanon == -1)
        {
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, b, w, w, w, b, b, w, w, w, b});
            _displayAttributes.push_back(std::vector<int> {w, w, b, w, w, w, w, b, w, w, w, w, b, w, w});
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, b, w, w, w, b, b, w, w, w, b});
        }
        else if(_currentCanon == 0)
        {
            _displayAttributes.push_back(std::vector<int> {r, r, r, r, r, b, w, w, w, b, b, w, w, w, b});
            _displayAttributes.push_back(std::vector<int> {r, w, r, w, r, w, w, b, w, w, w, w, b, w, w});
            _displayAttributes.push_back(std::vector<int> {r, r, r, r, r, b, w, w, w, b, b, w, w, w, b});
        }
        else if(_currentCanon == 1)
        {
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, r, r, r, r, r, b, w, w, w, b});
            _displayAttributes.push_back(std::vector<int> {w, w, b, w, w, r, w, r, w, r, w, w, b, w, w});
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, r, r, r, r, r, b, w, w, w, b});
        }
        else
        {
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, b, w, w, w, b, r, r, r, r, r});
            _displayAttributes.push_back(std::vector<int> {w, w, b, w, w, w, w, b, w, w, r, w, r, w, r});
            _displayAttributes.push_back(std::vector<int> {b, w, w, w, b, b, w, w, w, b, r, r, r, r, r});
        }*/
    }
    else
    {
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 15; j++)
				if (rand() % 32 == 0)
					_displayAttributes[i][j] = r;
    }
}
