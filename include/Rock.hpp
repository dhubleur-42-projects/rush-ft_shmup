/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rock.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 16:10:34 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 23:17:48 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROCK_HPP
# define ROCK_HPP

# include "Ennemy.hpp"
# include <string>
# include <vector>

class Rock: public Ennemy
{
    public:
        Rock(Rock const &src);
        Rock(int x, int y, int t);

        Rock	&operator=(Rock const &rhs);

    private:
};

#endif
