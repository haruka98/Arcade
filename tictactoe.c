#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <libpq-fe.h>
#include <windows.h>

#include "header.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int tictactoe(int special) {
	int feld[3][3] = {
		{0,0,0},
		{0,0,0},
		{0,0,0}
	};
	int quit = 0;
	int spieler = 1;
	int can_use_mouse = 1;
	SDL_Event e;
	int x = 0;
	int y = 0;
	while(quit == 0) {
		if(spieler == 3) {
			spieler = 1;
		}
		//test ob jemand gewonnen hat
		if((feld[0][0] == feld[0][1] && feld[0][0] == feld[0][2] && feld[0][0] != 0)
		|| (feld[0][0] == feld[1][0] && feld[0][0] == feld[2][0] && feld[0][0] != 0)
		|| (feld[1][1] == feld[0][0] && feld[1][1] == feld[2][2] && feld[1][1] != 0)
		|| (feld[1][1] == feld[0][2] && feld[1][1] == feld[2][0] && feld[1][1] != 0)
		|| (feld[1][1] == feld[0][1] && feld[1][1] == feld[2][1] && feld[1][1] != 0)
		|| (feld[1][1] == feld[1][0] && feld[1][1] == feld[1][2] && feld[1][1] != 0)
		|| (feld[2][2] == feld[0][2] && feld[2][2] == feld[1][2] && feld[2][2] != 0)
		|| (feld[2][2] == feld[2][0] && feld[2][2] == feld[2][1] && feld[2][2] != 0)) {
			quit = 1;
		}
		int nullen = 0;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(feld[i][j] == 0) {
					nullen++;
				}
			}
		}
		if(nullen == 0 && quit != 1) {
			//unentschieden
			quit = 1;
			spieler = -1;
		}
		//Eingaben
		while(SDL_PollEvent(&e) != 0) {
			if(SDL_MOUSEBUTTONUP) {
				can_use_mouse = 1;
			}
			if(e.type == SDL_QUIT) {
				quit = 1;
				return 0;
			} else {
				if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN && can_use_mouse == 1) {
					if(e.type == SDL_MOUSEBUTTONDOWN) {
						can_use_mouse = 0;
					}
					if(e.key.keysym.sym == SDLK_ESCAPE) {
						quit = 1;
						return 0;
					}
					if(e.key.keysym.sym == SDLK_F1) {
						tictactoe_help();
					}
					if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {
						if(x > (SCREEN_WIDTH / 2) - 180 && x < (SCREEN_WIDTH / 2) + 180 && y > (SCREEN_HEIGHT / 2) - 180 && y < (SCREEN_HEIGHT / 2) + 180) {
							//klick im feld
							x = x - (SCREEN_WIDTH / 2) - 180;
							y = y - (SCREEN_HEIGHT / 2) - 180;
							x = 2 + x / 120;
							y = 2 + y / 120;
							if(feld[x][y] == 0) {
								feld[x][y] = spieler;
								spieler++;
							}
						}
					}
				}
			}
		}	//Ende Event
		//render
		clear_render();
		render_tictactoe(feld, special);
		//render_test_circle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 45);
		render();
	} //ende quit
	if(spieler == 2) {
		spieler = 1;
	} else {
		if(spieler == 1) {
			spieler = 2;
		}
	}
	clear_render();
	render_tictactoe(feld, special);
	if(spieler != -1) {
		char* winner;
		winner = (char *) malloc(100 * sizeof(char));
		sprintf(&winner,"%d",spieler);
		winner = addstring("Spieler ", &winner);
		winner = addstring(winner, " gewinnt!");
		render_qango_player(winner);
	}
	if(spieler == -1) {
		char* winner;
		winner = (char *) malloc(100 * sizeof(char));
		sprintf(winner,"Unentschieden");
		render_qango_player(winner);
	}
	render();
	SDL_Event event;
	SDL_FlushEvent(&event);
	int exit = 0;
	do {
		SDL_PollEvent(&event);
		if(event.key.keysym.sym == SDLK_ESCAPE) {
			exit = 1;
		}
	} while(exit == 0);
	return 0;
}