/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ennemy.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:15:19 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 14:31:32 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENNEMY_HPP
# define ENNEMY_HPP

# include <ncurses.h>
# include <string>
# include <vector>
# include "Entity.hpp"
# include "Player.hpp"

class	Ennemy : public Entity
{
	public:
		//Constructors
		Ennemy(void);
		Ennemy(Ennemy const &src);
		Ennemy(int x, int y, bool killable);

		//Destructor
		virtual ~Ennemy(void);

		//Operators
		Ennemy	&operator=(Ennemy const &rhs);

		//Getters / Setters
		int    getFramesToFall(void) const;
        int    getFramesFromLastFall(void) const;
		int    getFramesToShoot(void) const;
        int    getFramesFromLastShoot(void) const;
		bool 	isKillable(void) const;
		std::string getType(void) const;

		//Methods
		virtual void	update(void);
		bool			exist(void) const;
		bool intersect(Player &player) const;

	protected:
		int 	_framesToFall;
        int 	_framesFromLastFall;
		bool 	_killable;
		int	    _framesToShoot;
		int		_framesFromLastShoot;
		std::string _type;
};

#endif
