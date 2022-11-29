/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BackgroundDot.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:59:00 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 03:52:59 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUNDDOT_HPP
# define BACKGROUNDDOT_HPP

# include <ncurses.h>

class	BackgroundDot
{
    public:
        BackgroundDot(BackgroundDot const &src);
        BackgroundDot(void);
		BackgroundDot(int x);
        ~BackgroundDot(void);
        BackgroundDot	&operator=(BackgroundDot const &rhs);

		int	getX(void) const { return (_x); }
		int	getY(void) const { return (_y); }
		int	getI(void) const { return (_i); }
		int	getIMax(void) const { return (_iMax); }
		int	getC(void) const { return (_c); }

		bool	isOutOfScreen(void) const;

		void	display(WINDOW *w) const;
		void	update(void);

    private:
		int		_x;
		int		_y;
		int		_i;
		int		_iMax;
		char	_c;
};

#endif
