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

int tron(int speed, int special) {
	int spielfeld[60][80];
	for(int i = 0; i < 60; i++) {	//leeres spielfeld
		for(int j = 0; j < 80; j++) {
			spielfeld[i][j] = 0;
		}
	}
	int alive_1 = 1;
	int alive_2 = 1;
	int x_1 = 3;
	int y_1 = 30;
	int x_2 = 76;
	int y_2 = 30;
	int dir_1 = 1;
	int dir_2 = 3;		//1 rechts, 2 unten, 3 links, 4 oben
	int quit = 0;
	int winner = 0;
	int timer = 0;
	int can_use_mouse = 1;
	SDL_Event e;
	int x = 0;
	int y = 0;
	if(special == 1 && speed > 9) {
		speed = speed - 6;
	}
	while(quit == 0) {
		timer++;
		if(timer >= 10 * speed) {
			timer = 0;
			if(dir_1 == 1) {
				x_1++;
			}
			if(dir_1 == 2) {
				y_1++;
			}
			if(dir_1 == 3) {
				x_1--;
			}
			if(dir_1 == 4) {
				y_1--;
			}
			if(dir_2 == 1) {
				x_2++;
			}
			if(dir_2 == 2) {
				y_2++;
			}
			if(dir_2 == 3) {
				x_2--;
			}
			if(dir_2 == 4) {
				y_2--;
			}
			if(x_1 < 0 || y_1 < 0 || x_1 > 79 || y_1 > 59 || spielfeld[y_1][x_1] != 0) {	//außerhalb des Bereiches (sp1)
				winner = 2;
				quit = 1;
			} else {
				spielfeld[y_1][x_1] = 1;
			}
			if(x_2 < 0 || y_2 < 0 || x_2 > 79 || y_2 > 59 || spielfeld[y_2][x_2] != 0) {	//außerhalb des Bereiches (sp2)
				winner = 1;
				quit = 1;
			} else {
				spielfeld[y_2][x_2] = 2;
			}
		} //timer end
		
		//Mouse Events
		while(SDL_PollEvent(&e) != 0) {
			if(SDL_MOUSEBUTTONUP) {
				can_use_mouse = 1;
			}
			if(e.type == SDL_QUIT) {
				quit = 1;
			} else {
				if(e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN && can_use_mouse == 1) {
					if(e.type == SDL_MOUSEBUTTONDOWN) {
						can_use_mouse = 0;
					}
					if(e.key.keysym.sym == SDLK_ESCAPE) {
						quit = 1;
					}
					if(e.key.keysym.sym == SDLK_w && dir_1 != 2) {
						dir_1 = 4;
					}
					if(e.key.keysym.sym == SDLK_a && dir_1 != 1) {
						dir_1 = 3;
					}
					if(e.key.keysym.sym == SDLK_s && dir_1 != 4) {
						dir_1 = 2;
					}
					if(e.key.keysym.sym == SDLK_d && dir_1 != 3) {
						dir_1 = 1;
					}
					if(e.key.keysym.sym == SDLK_UP && dir_2 != 2) {
						dir_2 = 4;
					}
					if(e.key.keysym.sym == SDLK_LEFT && dir_2 != 1) {
						dir_2 = 3;
					}
					if(e.key.keysym.sym == SDLK_DOWN && dir_2 != 4) {
						dir_2 = 2;
					}
					if(e.key.keysym.sym == SDLK_RIGHT && dir_2 != 3) {
						dir_2 = 1;
					}
					
					if(e.key.keysym.sym == SDLK_F1) {
						tron_help();
					}
				}
			}
		}	//Ende Event
		clear_render();
		render_tron(spielfeld);
		render_tron_spitze(x_1, y_1, special);
		render_tron_spitze(x_2, y_2, special);
		render();
	}	//ende quit
	if(winner == 0) {
		return 0;
	} else {
		clear_render();
		render_tron(spielfeld);
		render_tron_spitze(x_1, y_1, special);
		render_tron_spitze(x_2, y_2, special);
		//render_tron_winner();
		render();
		SDL_Event event;
		//SDL_FlushEvent(event);
		if(event.key.keysym.sym == SDLK_ESCAPE) {
			event.key.keysym.sym = SDLK_UP;
		}
		int exit = 0;
		do {
			SDL_PollEvent(&event);
			if(event.key.keysym.sym == SDLK_ESCAPE) {
				exit = 1;
			}
		} while(exit == 0);
		return 0;
	}
}