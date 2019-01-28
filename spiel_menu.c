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

int spiel_menu(int speed_tron, int special) {
	int quit = 0;
	int can_use_mouse = 1;
	int x = 0;
	int y = 0;
	SDL_Event e;
	while(quit == 0) {
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
					//Knöpfe
					if(e.key.keysym.sym == SDLK_ESCAPE) {
						quit = 1;
					}
					if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {
						if(x < 190 && x > 80 && y < 150 && y > 80) {	//Qango (Button 1)
							quit = 1;
							int a = qango();
						}
					}
					if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {
						if(x < 370 && x > 260 && y < 150 && y > 80) {	//Tron (Button 2)
							quit = 1;
							int a = tron(speed_tron, special);
						}
					}
					if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {
						if(x < 550 && x > 440 && y < 150 && y > 80) {	//Tic Tac Toe (Button 3)
							quit = 1;
							int a = tictactoe(special);
						}
					}
				}
			}
		}	//Ende event
		//clear_render();
		if(quit == 0) {
			SDL_GetMouseState(&x, &y);
			if(x < 190 && x > 80 && y < 150 && y > 80) {
				spiel_menu_render_qango();
			} else {
				if(x < 370 && x > 260 && y < 150 && y > 80) {
					spiel_menu_render_tron();
				} else {
					if(x < 550 && x > 440 && y < 150 && y > 80) {
						spiel_menu_render_tictactoe();
					} else {
						spiel_menu_render();
					}
				}
			}
			
		}
		//render();
	}
	return 0;
}