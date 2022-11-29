/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhubleur <dhubleur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 01:22:52 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/08/28 22:49:57 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <ncurses.h>
#include <thread>
#include "Game.hpp"
#include "Parameters.hpp"
#include "StartMenu.hpp"
#include "EndMenu.hpp"

WINDOW *screen;
WINDOW *windowGame;
WINDOW *windowUi;

static void	init_colors(void)
{
	start_color();
	init_color(COLOR_BACKGROUND1, 800, 810, 790);
	init_color(COLOR_BACKGROUND2, 705, 700, 680);
	init_color(COLOR_BACKGROUND3, 595, 600, 650);
	init_color(COLOR_BACKGROUND4, 505, 505, 500);
	init_color(COLOR_BACKGROUND5, 450, 405, 405);
	init_color(COLOR_BACKGROUND6, 300, 300, 310);
	init_color(COLOR_BROWN1, 550, 320, 20);
	init_color(COLOR_BROWN2, 530, 300, 20);
	init_color(COLOR_BROWN3, 520, 290, 30);
	init_color(COLOR_BROWN4, 500, 270, 20);
	init_color(COLOR_GREY, 600, 600, 600);
	init_pair(PAIR_BACKGROUND1, COLOR_BACKGROUND1, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND2, COLOR_BACKGROUND2, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND3, COLOR_BACKGROUND3, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND4, COLOR_BACKGROUND4, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND5, COLOR_BACKGROUND5, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND6, COLOR_BACKGROUND6, COLOR_BLACK);
	init_pair(PAIR_BROWN1, COLOR_BROWN1, COLOR_BLACK);
	init_pair(PAIR_BROWN2, COLOR_BROWN2, COLOR_BLACK);
	init_pair(PAIR_BROWN3, COLOR_BROWN3, COLOR_BLACK);
	init_pair(PAIR_BROWN4, COLOR_BROWN4, COLOR_BLACK);
	init_pair(PAIR_BACKGROUND_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(PAIR_BACKGROUND_GREY, COLOR_BLACK, COLOR_GREY);
	init_pair(PAIR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(PAIR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(PAIR_LIGHT_BROWN, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PAIR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

void	terminate(void)
{
	std::system("xset r rate");
	endwin();
}

void	init(void)
{
	screen = initscr();
	init_colors();
	cbreak();
	noecho();
	mouseinterval(0);
	keypad(screen, TRUE);
	curs_set(false);
	nodelay(screen, 1);
	mousemask(ALL_MOUSE_EVENTS, 0);
	wclear(screen);
	wrefresh(screen);
	srand(time(NULL));
	std::system("xset r rate 100 60");
}

void	run(int nbPlayers)
{
	StartMenu menu = StartMenu();
	while(!menu.isEnded())
	{
		menu.display(screen);
		menu.handleInput(screen);
	}
	windowGame = newwin(LINES_GAME, COLS_GAME,
		(LINES - LINES_GAME) / 2, (COLS - COLS_GAME) / 2);
	windowUi = newwin(LINES_UI, COLS_UI, 0, (COLS - COLS_UI) / 2);
	wclear(windowGame);
	wclear(windowUi);
	wrefresh(windowGame);
	wrefresh(windowUi);
	if(!menu.isKilled())
	{
		Game	game = Game(nbPlayers);
		while (!game.isTerminated())
		{		
			game.handleInput(windowGame, windowUi);
			game.update();
			game.display(windowGame, windowUi);
			std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_TIME));
			
		}
		wclear(screen);
		wrefresh(screen);
		std::chrono::_V2::system_clock::time_point end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - game.getStart();
		int time = elapsed_seconds.count() * 1000;
		EndMenu menu2 = EndMenu(time, game.getScore());
		while(!menu2.isEnded())
		{
			menu2.display(screen);
			menu2.handleInput(screen);
		}
	}
}

int	main(int argc, char **argv)
{
	int	nbPlayers;

	nbPlayers = 1;
	if (argc == 2 && argv[1][0] == '2' && argv[1][1] == 0)
		nbPlayers = 2;
	init();
	run(nbPlayers);
	terminate();
	return (0);
}
