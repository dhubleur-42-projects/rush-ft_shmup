/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:19:57 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 22:00:17 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parameters.hpp"
#include "Player.hpp"

//Constructors
Player::Player(void) : Entity(), _lives(DEFAULT_LIVES) , _vx(0), _vy(0), _damaged(0), _lastShoot(0), _canonPower(DEFAULT_CANON_POWER), _shieldPower(DEFAULT_SHIELD_POWER), _shieldFrame(0)
{
	_display = std::vector<std::string>();
	_display.push_back("  ^  ");
	_display.push_back("==|==");
	_display.push_back(" vvv ");
    _displayAttr = std::vector<std::vector<int>>();
}

Player::Player(Player const &src)
{
	*this = src;
}

Player::Player(int x, int y, int magneted) : Entity(x, y), _lives(DEFAULT_LIVES), _vx(0), _vy(0), _damaged(0), _lastShoot(0), _canonPower(DEFAULT_CANON_POWER), _shieldPower(DEFAULT_SHIELD_POWER), _shieldFrame(0)
{
	int	c;

	_magneted = magneted;
	_magnetX = _x;
	_magnetY = _y;
	_display = std::vector<std::string>();
	_display.push_back("  ^  ");
	_display.push_back("==|==");
	_display.push_back(" vvv ");
	if (_magneted)
		c = COLOR_PAIR(PAIR_MAGENTA);
	else
		c = COLOR_PAIR(PAIR_RED);
	_displayAttr = std::vector<std::vector<int>>();
    _displayAttr.push_back(std::vector<int> {0, 0, c, 0, 0});
    _displayAttr.push_back(std::vector<int> {c, c, 0, c, c});
    _displayAttr.push_back(std::vector<int> {0, c, c, c, 0});
}


//Operators
Player& Player::operator=(Player const &rhs)
{
	Entity::operator=(rhs);
	_lives = rhs.getLives();
	_vx = rhs.getVelX();
	_vy = rhs.getVelY();
	_magneted = rhs.getMagneted();
	_magnetX = rhs.getMagnetX();
	_magnetY = rhs.getMagnetY();
	_damaged = 0;
	_lastShoot = rhs.getLastShoot();
	_canonPower = rhs.getCanonPower();
	_shieldPower = rhs.getShieldPower();
	_shieldFrame = rhs.getShieldFrame();
	return (*this);
}


//Destructor
Player::~Player(void)
{
}


//Getters / Setters
int		Player::getLives(void) const
{
	return (_lives);
}
int		Player::getVelX(void) const
{
	return (_vx);
}
int		Player::getVelY(void) const
{
	return (_vy);
}
int		Player::getMagneted(void) const
{
	return (_magneted);
}
int		Player::getMagnetX(void) const
{
	return (_magnetX);
}
int		Player::getMagnetY(void) const
{
	return (_magnetY);
}
void	Player::setLives(int lives)
{
	_lives = lives;
}
void	Player::setVel(int vx, int vy)
{
	_vx = vx;
	_vy = vy;
}
void	Player::setMagneted(int magneted)
{
	_magneted = magneted;
}
void	Player::setMagnet(int x, int y)
{
	_magnetX = x;
	_magnetY = y;
}
int	Player::getLastShoot(void) const
{
	return (_lastShoot);
}
void	Player::shooted(void)
{
	_lastShoot = 8;
}

int		Player::getCanonPower(void) const
{
	return (_canonPower);
}
void	Player::increaseCanonPower(void)
{
	if(_canonPower < 3)
		++_canonPower;
}
int		Player::getShieldPower(void) const
{
	return (_shieldPower);
}
void	Player::increaseShieldPower(void)
{
	if(_shieldPower < 3)
		++_shieldPower;
}
int		Player::getShieldFrame(void) const
{
	return (_shieldFrame);
}
void	Player::useShield(void)
{
	if(_shieldFrame == 0)
	{
		_shieldPower--;
		_shieldFrame = 600;
	}
}
void Player::useCanon(void)
{
	_canonPower--;
}

void	Player::newScore(int score)
{
	if(score % 1000 == 0)
		increaseShieldPower();
	else if(score % 500 == 0)
		increaseCanonPower();
}

void	Player::increaseLife(void)
{
	++_lives;
}

//Methods
void	Player::hurt(void)
{
	if(_shieldFrame == 0)
	{
		_lives--;
		_damaged = 30;
	}
}
int		Player::isDead(void) const {
	return (_lives <= 0);
}
void	Player::update(void)
{
	if(_lastShoot > 0)
		--_lastShoot;
	_vy += -5 * (_vy > 0) + 5 * (_vy < 0);
	if (_magneted)
		_vy = 5 * (_y - _magnetY + 2 < 0)
			- 5 * (_y - _magnetY - 2 > 0);
	int toX = _x + _vx;
	int toY = _y + _vy;
	if (toX <= 5)
		_vx = 0;
	if (toX > LINES_GAME - LINES_PLAYER)
		_vx = 0;
	if (toY <= 0)
		_vy = 0;
	if (toY >= COLS_GAME - COLS_PLAYER)
		_vy = 0;
	_x += _vx;
	_y += _vy;
	if(_damaged > 0)
	{
		_display = std::vector<std::string>();
		_display.push_back("  ^  ");
		_display.push_back("==|==");
		_display.push_back(" vvv ");
		_displayAttr = std::vector<std::vector<int>>();
		int r = COLOR_PAIR(PAIR_RED);
		_displayAttr.push_back(std::vector<int> {0, 0, r, 0, 0});
		_displayAttr.push_back(std::vector<int> {r, r, r, r, r});
		_displayAttr.push_back(std::vector<int> {0, r, r, r, 0});
		--_damaged;
	}
	else if(_shieldFrame > 0)
	{
		_display = std::vector<std::string>();
		_display.push_back("--^--");
		_display.push_back("==|==");
		_display.push_back(" vvv ");
		_displayAttr = std::vector<std::vector<int>>();
		int r = COLOR_PAIR(PAIR_LIGHT_BROWN);
		int b = COLOR_PAIR(PAIR_BLUE);
		_displayAttr.push_back(std::vector<int> {b, b, r, b, b});
		_displayAttr.push_back(std::vector<int> {r, r, r, r, r});
		_displayAttr.push_back(std::vector<int> {0, r, r, r, 0});
		--_shieldFrame;
	}
	else
	{
		_display = std::vector<std::string>();
		_display.push_back("  ^  ");
		_display.push_back("==|==");
		_display.push_back(" vvv ");
		_displayAttr = std::vector<std::vector<int>>();
		int b = _magneted?COLOR_PAIR(PAIR_MAGENTA):COLOR_PAIR(PAIR_LIGHT_BROWN);
		_displayAttr.push_back(std::vector<int> {0, 0, b, 0, 0});
		_displayAttr.push_back(std::vector<int> {b, b, 0, b, b});
		_displayAttr.push_back(std::vector<int> {0, b, b, b, 0});
	}
}
void	Player::goLeft(void)
{
	_vy = -10;
}
void	Player::goRight(void)
{
	_vy = 10;
}
