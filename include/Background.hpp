/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Background.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:39:26 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 05:09:56 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_HPP
# define BACKGROUND_HPP

# include <ncurses.h>
# include <vector>
# include "BackgroundDot.hpp"

class	Background
{
	public:
		Background(Background const &src);
		Background(void);
		~Background(void);
		Background	&operator=(Background const &rhs);

		std::vector<BackgroundDot>	getDots(void) const;

		void						display(WINDOW *w) const;
		void						update(void);

	private:
		std::vector<BackgroundDot>	_dots;
};

#endif
