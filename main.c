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

int main(int argc, char* argv[]) {
	int show_menue = 1;
	int show_settings = 0;
	int can_use_mouse = 1;
	int speed_tron = 10;
	int special = 0;
	int konami = 0;
	int x = 0;
	int y = 0;
	if(init_sdl("Game") != 0) {
		printf("Failed to initialize!\n");
	} else {
		//Program start
		int quit = 0;
		SDL_Event e;
		while(quit == 0) {
			if(konami > 9) {
				special = 1;
			}
			//Handle events on queue
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
						if(show_menue == 1) {	//Menü
							if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {			//Maus kann gedrückt gehalten werden?
								if(x < 550 && x > 250 && y < 355 && y > 325) {	//Beenden (Button 3)
									show_menue = 0;
									quit = 1;
								}
								if(x < 550 && x > 250 && y < 275 && y > 245) {	//Spiel start (Button 1)
									int a = spiel_menu(speed_tron, special);
									show_menue = 1;
								}
								if(x < 550 && x > 250 && y < 315 && y > 285) {	//Einstellungen (Button 2)
									show_menue = 0;
									show_settings = 1;
								}
							}
							if(e.key.keysym.sym == SDLK_ESCAPE) {
								quit = 1;
							}
							
							if(e.key.keysym.sym == SDLK_a && konami != 9) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_a && konami == 9) {
								konami++;
							}
							if(e.key.keysym.sym == SDLK_b && konami != 8) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_b && konami == 8) {
								konami++;
							}
							if(e.key.keysym.sym == SDLK_RIGHT && konami != 5 && konami != 7) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_RIGHT && konami == 5 || e.key.keysym.sym == SDLK_RIGHT && konami == 7) {
								konami++;
							}
							if(e.key.keysym.sym == SDLK_LEFT && konami != 4 && konami != 6) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_LEFT && konami == 4 || e.key.keysym.sym == SDLK_LEFT && konami == 6) {
								konami++;
							}
							if(e.key.keysym.sym == SDLK_DOWN && konami != 2 && konami != 3) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_DOWN && konami > 1 && konami < 4) {
								konami++;
							}
							if(e.key.keysym.sym == SDLK_UP && konami != 0 && konami != 1) {
								konami = 0;
							}
							if(e.key.keysym.sym == SDLK_UP && konami < 2) {
								konami++;
							}
							
						}
						if(show_settings == 1) {	//Settings
							if(e.key.keysym.sym == SDLK_ESCAPE) {	//Zurück zum Hauptmenü
								show_menue = 1;
								show_settings = 0;
							}
							if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {
								if(x < 110 && x > 30 && y < 570 && y > 540) {	//Zurück zum Hauptmenü (Button 1)
									show_menue = 1;
									show_settings = 0;
								}
								if(x < 400 + 250 && x > 400 - 250 && y < 300 + 25 - 50 && y > 300 - 25 - 50) {	//Tron Speed (Button 2)
									switch(speed_tron) {
										case 1: speed_tron = 20; break;
										case 5: speed_tron = 1; break;
										case 10: speed_tron = 5; break;
										case 15: speed_tron = 10; break;
										case 20: speed_tron = 15; break;
									}
								}
							}
						}
					}
				}
			}
			clear_render();
			render_background(special);
			if(show_menue == 1) {
				render_menue();
			}
			if(show_settings == 1) {
				render_settings(speed_tron);
			}
			
			render();
		}
		close_sdl();
		return 0;
	}
}