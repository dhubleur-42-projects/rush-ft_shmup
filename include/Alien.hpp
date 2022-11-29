/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Alien.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:10:34 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 23:17:58 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIEN_HPP
# define ALIEN_HPP

# include "Ennemy.hpp"
# include <string>
# include <vector>

class Alien: public Ennemy
{
    public:
        Alien(Alien const &src);
        Alien(int x, int y, int t);

        Alien	&operator=(Alien const &rhs);

    private:
};

#endif
