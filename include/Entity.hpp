/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 02:15:19 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 05:01:47 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <ncurses.h>
# include <string>
# include <vector>

class	Entity
{
	public:
		//Constructors
		Entity(void);
		Entity(Entity const &src);
		Entity(int x, int y);

		//Destructor
		virtual ~Entity(void);

		//Operators
		Entity	&operator=(Entity const &rhs);

		//Getters / Setters
		int		getPosX() const;
		int		getPosY() const;
		std::vector<std::string>		getDisplay() const;
		std::vector<std::vector<int>>	getDisplayAttr() const;
		void	setPos(int x, int y);
		void	setDisplay(std::vector<std::string> display);
		void	setDisplayAttr(std::vector<std::vector<int>> displayAttr);

		//Methods
		void	display(WINDOW *w) const;

	protected:
		int		_x;
		int		_y;
		std::vector<std::string>		_display;
		std::vector<std::vector<int>>	_displayAttr;
};

#endif
