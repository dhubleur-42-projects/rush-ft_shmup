/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:44:41 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 23:13:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "Game.hpp"
#include "Parameters.hpp"
#include "Rock.hpp"
#include "Alien.hpp"

//Constructors
Game::Game(int nbPlayers) :
	_title("ft_shmup"),
	_nbPlayers(nbPlayers),
	_ennemies(std::vector<Ennemy>()),
	_rays(std::vector<Ray>()),
	_fSpawnAlien(80),
	_fSpawnRock(40),
	_stopped(false),
	_score(0),
	_diffcultyLevel(1),
	_nextDifficultyIn(30*60),
	_bossTime(false),
	_spawnedBoss(false)
{
	if (_nbPlayers == 1)
		_player = Player(LINES_GAME - 8, COLS_GAME / 2, 0);
	if (_nbPlayers == 2)
	{
		_player = Player(LINES_GAME - 8, COLS_GAME / 4, 0);
		_player2 = Player(LINES_GAME - 8, COLS_GAME * 3 / 4, 1);
	}
	_start = std::chrono::system_clock::now();
	_lastBoss = _start;
}

Game::Game(Game const &src)
{
	*this = src;
}


//Operators
Game &Game::operator=(Game const &rhs)
{
	_title = rhs.getTitle();
	_player = rhs.getPlayer();
	return (*this);
}


//Destructor
Game::~Game(void)
{}

//Getters / Setters
int	Game::isTerminated(void) const
{
	return (_player.isDead() || _player2.isDead() || _stopped);
}
std::string	Game::getTitle(void) const
{
	return (_title);
}
Player		Game::getPlayer(void) const
{
	return (_player);
}
Player		Game::getPlayer2(void) const
{
	return (_player2);
}

//Methods
void	Game::display(WINDOW *wGame, WINDOW *wUi) const
{
	_displayInfos(wUi);
	_background.display(wGame);
	_player.display(wGame);
	if (_nbPlayers == 2)
		_player2.display(wGame);
	for(Ennemy enn : _ennemies)
		enn.display(wGame);
	if(_spawnedBoss)
		_boss.display(wGame);
	for(Ray ray : _rays)
		ray.display(wGame);
	wrefresh(wGame);
}

static bool isRayEnd(const Ray & ray)
{
    return !ray.exist();
}
static bool isEnnemyOnScreen(const Ennemy & ent)
{
	return !ent.exist();
}

std::chrono::_V2::system_clock::time_point	Game::getStart(void) const
{
	return (_start);
}

int	Game::getScore(void) const
{
	return (_score);
}

void	Game::update(void)
{
	if(COLS > COLS_GAME && LINES > 50)
	{
		_player.update();
		if (_nbPlayers == 2)
			_player2.update();
		_background.update();

		// Update ennemies
		for(std::vector<Ennemy>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it)
			(*it).update();

		//Update rays
		for(std::vector<Ray>::iterator it = _rays.begin(); it != _rays.end(); ++it)
		{
			Ray &ray = *it;
			ray.update();
		}

		//Aliens shoots
		for(std::vector<Ennemy>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it)
		{
			Ennemy &enn = *it;
			if(enn.getType() == "alien")
			{
				if(enn.getFramesFromLastShoot() == 0)
				{
					int distX = _player.getPosX() - enn.getPosX();
					int distY = _player.getPosY() - enn.getPosY();
					if(distY == 0)
						_rays.push_back(Ray(enn.getPosX() + 4, enn.getPosY() + 2, 1, 0));
					else if(abs(distX) > abs(distY))
						_rays.push_back(Ray(enn.getPosX() + 4, enn.getPosY() + 2, 1, 0));
					else if(abs(distX) < abs(distY))
						_rays.push_back(Ray(enn.getPosX() + 4, enn.getPosY() + 2, 1, distY < 0 ? -1 : 1));
				}
			}
		}
		if(_spawnedBoss)
		{
			if(_boss.getFrameToShoot() == _boss.getLastShoot())
			{
				for(int i = 0; i < 3; i++)
				{
					if(_boss.getCanonLife(i) > 0)
					{
						_rays.push_back(Ray(_boss.getX() + 9, _boss.getY() + (i == 0 ? 2 : i == 1 ? 7 : 12) + (_boss.getDestY() == 10 ? -5 : _boss.getDestY() == 0 ? 0 : 5), 1, 0));
					}
				}
			}
			if(_boss.getAfterDeath() >= 5*60)
			{
				_bossTime = false;
				_spawnedBoss = false;
				_player.increaseLife();
				_player.increaseCanonPower();
				_player.increaseShieldPower();
				_score += 500;
				_lastBoss = std::chrono::system_clock::now();
			}
		}

		// Check Rays collisions
		for(std::vector<Ray>::iterator it = _rays.begin(); it != _rays.end(); ++it)
		{
			Ray &ray = *it;
			int	erased = 0;
			for(std::vector<Ennemy>::iterator it2 = _ennemies.begin(); it2 != _ennemies.end(); ++it2)
			{
				Ennemy &ent = *it2;
				if(!erased && ray.intersect(ent))
				{
					if(ent.isKillable())
					{
						_score += 100;
						_player.newScore(_score);
						_ennemies.erase(it2--);
					}
					_rays.erase(it--);
					erased = 1;
				}
			}
			if(!erased && _spawnedBoss && _boss.intersect(ray))
			{
				_rays.erase(it--);
				erased = 1;
			}
			if(!erased && ray.intersect(_player))
			{
				_rays.erase(it--);
				erased = 1;
				_player.hurt();
			}
			if(!erased && _nbPlayers == 2 && ray.intersect(_player2))
			{
				_rays.erase(it--);
				erased = 1;
				_player2.hurt();
			}
		}

		for(std::vector<Ennemy>::iterator it = _ennemies.begin(); it != _ennemies.end(); ++it)
		{
			Ennemy &ent = *it;
			if(ent.intersect(_player))
			{
				_player.hurt();
				_ennemies.erase(it--);
			}
			else if(_nbPlayers == 2 && ent.intersect(_player2))
			{
				_player2.hurt();
				_ennemies.erase(it--);
			}
		}
		
		_rays.erase(std::remove_if(_rays.begin(), _rays.end(), isRayEnd), _rays.end());
		_ennemies.erase(std::remove_if(_ennemies.begin(), _ennemies.end(), isEnnemyOnScreen), _ennemies.end());

		--_nextDifficultyIn;
		if(_nextDifficultyIn <= 0)
		{
			_nextDifficultyIn = (rand()%5+25) * 60;
			_diffcultyLevel++;
		}
		
		std::chrono::_V2::system_clock::time_point bossEnd = std::chrono::system_clock::now();
		std::chrono::duration<double> bossElapsedSeconds = bossEnd - _lastBoss;
		int bossTotal = bossElapsedSeconds.count() * 1000 / 600;
		if(bossTotal == SECONDS_TO_SPAWN_BOSS)
			_bossTime = true;

		//	Update fSpawnEnnemies
		std::chrono::_V2::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - _start;
		if(!_bossTime)
		{
			int t = elapsed_seconds.count();
			_fSpawnAlien = (std::cos(t / 20 * 2 * M_PI) + 1.5) / 2.5 * (80 - 70 * t / (t + 180));
			_fSpawnRock = std::pow((std::cos(t / 12 * 2 * M_PI) + 1.5) / 2.5, 2) * (40 - 30 * t / (t + 90));

			//	Spawn ennemies
			while (rand() % _fSpawnAlien == 0)
				_spawnAlien(t);
			while (rand() % _fSpawnRock == 0)
				_spawnRock(t);
		}
		else
		{
			if(_ennemies.size() == 0 && !_spawnedBoss)
			{
				_spawnedBoss = true;
				_boss = Boss();
			}
			if(_spawnedBoss)
				_boss.update();
		}
	}
}

void	Game::_spawnAlien(int t)
{
	int x = 0;
	int positions = COLS_GAME / 5 - 2;
	int choosed = rand() % positions + 1;
	int y = choosed * 5;

	for(Ennemy ent : _ennemies)
		if(ent.getPosY() == y && ent.getType() == "alien")
			return ;
	Alien alien = Alien(x, y, t);
	_ennemies.push_back(alien);
}

void	Game::_spawnRock(int t)
{
	int x = 0;
	int positions = COLS_GAME / 5 - 2;
	int choosed = rand() % positions + 1;
	int y = choosed * 5;

	for(Ennemy ent : _ennemies)
		if(ent.getPosY() == y && ent.getType() == "alien")
			return ;
	Rock rock = Rock(x, y, t);
	_ennemies.push_back(rock);
}

void	Game::_displayInfos(WINDOW *w) const
{
	std::chrono::_V2::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - _start;
	int time = elapsed_seconds.count() * 1000;
	int minutes = time / 60000;
	int seconds = (time - minutes * 60000) / 1000;
	if (_nbPlayers == 1)
		mvwprintw(w, 3, 6, "Lives: %i", _player.getLives());
	mvwprintw(w, 3, 30, "Time: %s%i:%s%i", minutes >= 10 ? "" : "0", minutes, seconds >= 10 ? "" : "0", seconds);
	mvwprintw(w, 3, 55, "Score: %i", _score);
	mvwprintw(w, 3, 80, "Canon: %i", _player.getCanonPower());
	mvwprintw(w, 4, 80, "Shield: %i", _player.getShieldPower());
	if (_nbPlayers == 2)
	{
		mvwprintw(w, 3, 6, "P1 Lives: %i", _player.getLives());
		mvwprintw(w, 4, 6, "P2 Lives: %i", _player2.getLives());
	}
	if(COLS <= COLS_GAME || LINES <= 50)
		mvwprintw(w, 1, 1, "Window is too small");
	else
		mvwprintw(w, 1, 1, "                   ");
	wrefresh(w);
}

void	Game::handleInput(WINDOW *windowGame, WINDOW *windowUi)
{
	bool	c[0xFFFF] = {0};
	std::vector<int>	keys = std::vector<int>();
	int		buff;
	MEVENT	event;

	cbreak();
	buff = getch();
	while (buff != ERR)
	{
		if (buff >= 0 && buff < 0xFFFF && !c[buff])
		{
			c[buff] = 1;
			keys.push_back(buff);
		}
		cbreak();
		buff = getch();
	}
	for (int key : keys)
	{
		switch (key)
		{
		case KEY_LEFT:
		case 'A':
		case 'a':
			if(COLS > COLS_GAME && LINES > 50)
				_player.goLeft();
			break;
		case KEY_RIGHT:
		case 'D':
		case 'd':
			if(COLS > COLS_GAME && LINES > 50)
				_player.goRight();
			break;
		case 'Q':
		case 'q':
			_stopped = true;
			break;
		case KEY_UP:
		case 'W':
		case 'w':
		case ' ':
			if(COLS > COLS_GAME && LINES > 50 && _player.getLastShoot() == 0)
			{
				_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 2, -1, 0));
				_player.shooted();
			}
			break;
		case 'Z':
		case 'z':
			if(COLS > COLS_GAME && LINES > 50 && _player.getLastShoot() == 0
				&& _player.getCanonPower() > 0)
			{
				_player.useCanon();
				_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 2, -1, 0));
				if(_player.getPosY() - 3 > 0)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() - 3, -1, 0));
				if(_player.getPosY() - 8 > 0)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() - 8, -1, 0));
				if(_player.getPosY() - 13 > 0)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() - 13, -1, 0));
				if(_player.getPosY() + 7 < COLS_GAME)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 7, -1, 0));
				if(_player.getPosY() + 12 < COLS_GAME)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 12, -1, 0));
				if(_player.getPosY() + 17 < COLS_GAME)
					_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 17, -1, 0));
				_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 2, -1, 1));
				_rays.push_back(Ray(_player.getPosX() - 1, _player.getPosY() + 2, -1, -1));
				_player.shooted();
			}
			break;
		case 'X':
		case 'x':
			if(COLS > COLS_GAME && LINES > 50 && _player.getLastShoot() == 0
				&& _player.getShieldPower() > 0)
				_player.useShield();
			break;
		case KEY_MOUSE:
			if (getmouse(&event) == OK)
			{
				if (event.bstate & ALL_MOUSE_EVENTS)
				{
					event.x -= (COLS - COLS_GAME) / 2 + 2;
					event.y -= (LINES - LINES_GAME) / 2 + 2;
					if (event.x >= 0 && event.x < COLS_GAME
						&& event.y >= 0 && event.y < LINES_GAME)
					{
						_player.setMagnet(event.y, event.x);
						if (_nbPlayers == 2)
							_player2.setMagnet(event.y, event.x);
					}
				}
				if (_nbPlayers == 2 && event.bstate & BUTTON4_PRESSED
					&& COLS > COLS_GAME && LINES > 50 && _player2.getLastShoot() == 0)
				{
					_rays.push_back(Ray(_player2.getPosX() - 1, _player2.getPosY() + 2, -1, 0));
					_player2.shooted();
				}
			}
			break ;
		case KEY_RESIZE:
			mvwin(windowGame, (LINES - LINES_GAME) / 2, (COLS - COLS_GAME) / 2);
			mvwin(windowUi, 0, (COLS - COLS_UI) / 2);
			break;
		default:
			break;
		}
	}
}
