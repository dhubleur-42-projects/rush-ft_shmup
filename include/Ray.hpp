/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:21:12 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 17:53:30 by dhubleur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HPP
# define RAY_HPP

# include "Ennemy.hpp"
# include "Player.hpp"
# include "Boss.hpp"
# include <iostream>
# include <string>
# include <ncurses.h>

class Ray
{	
	public:
		// Constructors
		Ray();
		Ray(const Ray &copy);
		Ray(int x, int y, int vx, int vy);
		
		// Destructor
		~Ray();
		
		// Operators
		Ray & operator=(const Ray &assign);
		
		// Getters / Setters
		int getX() const;
		int getY() const;
		int getVx() const;
		int getVy() const;
		std::string			getDisplay() const;
		std::vector<int>	getDisplayAttr() const;

		//Methods
		void update(void);
		bool exist(void) const;
		void display(WINDOW *w) const;
		bool intersect(Ennemy &ent) const;
		bool intersect(Player &ent) const;
		int intersect(Boss &ent) const;

	private:
		void	computeDisplay(void);
		void	computeDisplayAttr(void);
		int _x;
		int _y;
		int _vx;
		int _vy;
		int	_dir;
		std::string			_display;
		std::vector<int>	_displayAttr;
};

#endif
