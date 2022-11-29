/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:08:30 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 19:17:42 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

#include "Entity.hpp"

class	Player: public Entity
{
	public:
		//Constructors
		Player(void);
		Player(Player const &src);
		Player(int x, int y, int magneted);

		//Destructor
		~Player(void);

		//Operaotrs
		Player	&operator=(Player const &rhs);
		//Getters / Setters
		int		getLives(void) const;
		void	setLives(int lives);
		int		getVelX() const;
		int		getVelY() const;
		void	setVel(int vx, int vy);
		int		getMagneted() const;
		void	setMagneted(int magneted);
		int		getMagnetX() const;
		int		getMagnetY() const;
		void	setMagnet(int x, int y);
		int		getLastShoot(void) const;
		void	shooted(void);
		int		getCanonPower(void) const;
		void	increaseCanonPower(void);
		int		getShieldPower(void) const;
		void	increaseShieldPower(void);
		int		getShieldFrame(void) const;
		void	useShield(void);
		void	useCanon(void);
		void	increaseLife(void);

		//Methods
		void	hurt(void);
		int		isDead(void) const;
		void	update(void);
		void	goLeft(void);
		void	goRight(void);
		void	newScore(int score);

	private:
		int	_lives;
		int	_vx;
		int	_vy;
		int	_magneted;
		int	_magnetX;
		int	_magnetY;
		int _damaged;
		int _lastShoot;
		int	_canonPower;
		int _shieldPower;
		int	_shieldFrame;
};

#endif
