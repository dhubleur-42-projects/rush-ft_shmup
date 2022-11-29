/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 22:26:20 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 23:37:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StartMenu.hpp"
#include "Parameters.hpp"
#include <string>


const std::string	art[] = {
    "     Shoot                      ",
    "      [^]        Canon  Shield  ",
    "  [<] [v] [>]     [Z]    [X]    ",
    " Left    Right                  "
};

const std::string	title[] = {
	"    ---   --                 --                                 ",
	"   --/   /--                /--                          ------ ",
	" ------ /-----        ------/--      ----------  --   --/--///--",
	"///--/  //--/        --//// /------ //--//--//--/--  /--/--  /--",
	"  /--    /--        //----- /--///-- /-- /-- /--/--  /--/------ ",
	"  /--    /--         /////--/--  /-- /-- /-- /--/--  /--/--///  ",
	"  /--    /---- ----- ------ /--  /-- --- /-- /--//------/--     ",
	"  //     //// ///// //////  //   // ///  //  //  ////// //      "};

StartMenu::StartMenu(void)
{
    _ended = false;
}

StartMenu::~StartMenu(void)
{
}

bool    StartMenu::isEnded(void)  const
{
    return _ended == 1 || _ended == 2;
}
bool   StartMenu::isKilled(void)  const
{
    return _ended == 2;
}

void    StartMenu::display(WINDOW *screen) const
{
    if(COLS > COLS_GAME && LINES > 50)
    {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < (int) title[i].size(); j++)
			{
				if (title[i][j] == '-')
				{
					wattron(screen, COLOR_PAIR(PAIR_BACKGROUND_WHITE));
					mvwaddch(screen, i + 7, COLS / 2 - 34 + j, ' ');
					wattroff(screen, COLOR_PAIR(PAIR_BACKGROUND_WHITE));
				}
				if (title[i][j] == '/')
					mvwaddch(screen, i + 7, COLS / 2 - 34 + j, title[i][j]);
			}
		}
        mvwprintw(screen, 20, COLS/2-5, "Start Menu");
        mvwprintw(screen, 21, COLS/2-10, "Press space to start");
        mvwprintw(screen, 22, COLS/2-7, "Press Q to quit");
        for(int i = 0; i < 4; i++)
        {
            mvwprintw(screen, i + 26, (COLS/2)-(art[i].length()/2), "%s", art[i].c_str());
        }
        wrefresh(screen);
    }
    else
    {
        mvwprintw(screen, 1, 1, "Window is too small");
        mvwprintw(screen, 2, 1, "Press Q to quit");
    }
    curs_set(false);
}

void    StartMenu::handleInput(WINDOW *screen)
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
				_ended = 2;
                break;
            case ' ':
                if(COLS > COLS_GAME && LINES > 50)
                            _ended = 1;
                break;
        }
    }
}
