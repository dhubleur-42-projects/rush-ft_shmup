/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EndMenu.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:02:00 by dhubleur          #+#    #+#             */
/*   Updated: 2022/08/28 22:59:24 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EndMenu.hpp"
#include "Parameters.hpp"
#include <string>

const std::string	title[] = {
	"    ---   --                 --                                 ",
	"   --/   /--                /--                          ------ ",
	" ------ /-----        ------/--      ----------  --   --/--///--",
	"///--/  //--/        --//// /------ //--//--//--/--  /--/--  /--",
	"  /--    /--        //----- /--///-- /-- /-- /--/--  /--/------ ",
	"  /--    /--         /////--/--  /-- /-- /-- /--/--  /--/--///  ",
	"  /--    /---- ----- ------ /--  /-- --- /-- /--//------/--     ",
	"  //     //// ///// //////  //   // ///  //  //  ////// //      "};

EndMenu::EndMenu(int elapsed_time, int scores)
{
    _elapsed_time = elapsed_time;
    _score = scores;
    _ended = false;
}

EndMenu::~EndMenu(void)
{
}

bool    EndMenu::isEnded(void)  const
{
    return _ended;
}

void    EndMenu::display(WINDOW *screen) const
{
    if(COLS > COLS_GAME && LINES > 50)
    {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < (int) title[i].size(); j++)
			{
				if (title[i][j] == '-')
				{
					wattron(screen, COLOR_PAIR(PAIR_BACKGROUND_GREY));
					mvwaddch(screen, i + 7, COLS / 2 - 34 + j, ' ');
					wattroff(screen, COLOR_PAIR(PAIR_BACKGROUND_GREY));
				}
				if (title[i][j] == '/')
					mvwaddch(screen, i + 7, COLS / 2 - 34 + j, title[i][j]);
			}
		}
        mvwprintw(screen, 20, COLS/2-5, "Game ended");
        mvwprintw(screen, 21, COLS/2-10, "Your score is:% 7.3d", _score);
        int minutes = _elapsed_time / 60000;
	    int seconds = (_elapsed_time - minutes * 60000) / 1000;
	    mvwprintw(screen, 24, COLS/2-9, "You survived: %s%i:%s%i", minutes >= 10 ? "" : "0", minutes, seconds >= 10 ? "" : "0", seconds);
        mvwprintw(screen, 25, COLS/2-7, "Press Q to quit");
        wrefresh(screen);
    }
    else
    {
        mvwprintw(screen, 1, 1, "Window is too small");
        mvwprintw(screen, 2, 1, "Press Q to quit");
    }
    curs_set(false);
}

void    EndMenu::handleInput(WINDOW *screen)
{
    (void)screen;
    int c;
    c = getch();
    if(c != ERR)
    {
        switch(c)
        {
            case 'Q':
			case 'q':
				_ended = true;
                break;
        }
    }
}
