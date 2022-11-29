/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:41:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 23:14:30 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Background.hpp"
# include "Player.hpp"
# include "Ray.hpp"
# include "Ennemy.hpp"
# include <string>
# include <ncurses.h>
# include <vector>
# include <algorithm>
# include <chrono>
# include <Boss.hpp>

# define FRAME_TIME 16

class	Game
{
	public:
		//Constructors
		Game(int nbPlayers);
		Game(Game const &src);

		//Destructor
		~Game(void);

		//Operators
		Game &operator=(Game const &rhs);
		
		//Getters / Setters
		int			isTerminated(void) const;
		std::string	getTitle(void) const;
		Player		getPlayer(void) const;
		Player		getPlayer2(void) const;
		std::chrono::_V2::system_clock::time_point	getStart(void) const;
		int			getScore(void) const;

		//Methods
		void	display(WINDOW *wGame, WINDOW *wUi) const;
		void	update(void);
		void	handleInput(WINDOW *windowGame, WINDOW *windowUi);

	private:
		std::string			_title;
		int					_nbPlayers;
		Player				_player;
		Player				_player2;
		std::vector<Ennemy>	_ennemies;
		Background			_background;
		std::vector<Ray>	_rays;
		int					_fSpawnAlien;
		int					_fSpawnRock;
		bool				_stopped;
		int					_score;
		std::chrono::_V2::system_clock::time_point		_start;
		int				_diffcultyLevel;
		int				_nextDifficultyIn;
		bool			_bossTime;
		bool			_spawnedBoss;
		Boss			_boss;
		std::chrono::_V2::system_clock::time_point		_lastBoss;

		void	_displayInfos(WINDOW *w) const;
		void	_spawnAlien(int t);
		void	_spawnRock(int t);
		void	_shoot(Entity shooter, int vx);
};

#endif
