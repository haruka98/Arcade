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

int qango() {
	int feld[6][6] = {		//Spielfeld
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0}
	};
	SDL_Event e;
	int player = 1;
	int quit = 0;
	int can_use_mouse = 1;
	int x = 0;
	int y = 0;
	int game = 1;	//Zeigt ob das Spiel noch aktiv ist, 0 um den Sieger bekannt zu geben.
	while(quit == 0) {
		if(player == 3) {
			player = 1;
		}
		clear_render();
		if(game == 1) {	//Hintergrund Spielfeld & Spieler <1/2> anzeige
			render_qango_field();
			render_qango_fig(feld);
			char* player_string;
			sprintf(&player_string,"%d",player);
			player_string = addstring("Spieler ", &player_string);
			render_qango_player(player_string);
		}
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
					if(e.key.keysym.sym == SDLK_F1) {
						qango_help();
					}
					if(SDL_BUTTON(SDL_GetMouseState(&x, &y)) == SDL_BUTTON_LEFT) {	//neue eingabe
						if(x > (SCREEN_WIDTH / 2) - 180 && x < (SCREEN_WIDTH / 2) + 180 && y > (SCREEN_HEIGHT / 2) - 180 && y < (SCREEN_HEIGHT / 2) + 180) {
							//klick im feld
							x = x - (SCREEN_WIDTH / 2) - 180;
							y = y - (SCREEN_HEIGHT / 2) - 180;
							x = 5 + x / 60;
							y = 5 + y / 60;
							printf("%d - %d\n",x,y);	//Testinfo, remove later
							if(feld[x][y] == 0) {
								feld[x][y] = player;
								int a = test_qango(feld, player);
								if(a == player) {
									//Spieler gewinnt
									game = 0;
									quit = 1;
									
									if(game == 0) {
										clear_render();
										render_qango_field();
										render_qango_fig(feld);
										char* winner;
										winner = (char *) malloc(100 * sizeof(char));
										sprintf(&winner,"%d",player);
										winner = addstring("Spieler ", &winner);
										winner = addstring(winner, " gewinnt!");
										render_qango_player(winner);
										render();
										SDL_Event event;
										do {
											SDL_PollEvent(&event);
										} while(event.type != SDL_KEYDOWN);
										free(winner);
									}
								}
								player++;
							}
							
							if(nullen_qango(feld) == 0 && quit != 1) {		//Unentschieden
								clear_render();
								render_qango_field();
								render_qango_fig(feld);
								char* unent;
								unent = (char *) malloc(100 * sizeof(char));
								sprintf(unent,"Unentschieden");
								render_qango_player(unent);
								render();
								SDL_Event event;
								game = 0;
								quit = 1;
								do {
									SDL_PollEvent(&event);
								} while(event.type != SDL_KEYDOWN);
								free(unent);
							}
						}
					}
					//Maus und Tastatur eingaben hier.
				}
			}
		}	//Ende Event
		render();
	}
	clear_render();
	return 0;
}

char* addstring(char* str1, char* str2) {
	char *string = malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(string, str1);
	strcat(string, str2);
	return string;
}

int nullen_qango(int feld[6][6]) {
	int nullen = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			if(feld[i][j] == 0) {
				nullen++;
			}
		}
	}
	return nullen;
}

int test_qango(int feld[6][6], int player) {
	//test linien
	for(int i = 0; i < 6; i++) {
		if(feld[i][1] == player && feld[i][2] == player && feld[i][3] == player && feld[i][4] == player) {
			if(feld[i][0] == player || feld[i][5] == player) {
				return player;
			}
		}
		if(feld[1][i] == player && feld[2][i] == player && feld[3][i] == player && feld[4][i] == player) {
			if(feld[0][i] == player || feld[5][i] == player) {
				return player;
			}
		}
	}
	//test diagonalen
	if(feld[1][1] == player && feld[2][2] == player && feld[3][3] == player && feld[4][4] == player) {
		if(feld[0][0] == player || feld[5][5] == player) {
			return player;
		}
	}
	if(feld[1][4] == player && feld[2][3] == player && feld[3][2] == player && feld[4][1] == player) {
		if(feld[0][5] == player || feld[5][0] == player) {
			return player;
		}
	}
	if(feld[0][1] == player && feld[1][2] == player && feld[2][3] == player && feld[3][4] == player && feld[4][5] == player) {
		return player;
	}
	if(feld[1][0] == player && feld[2][1] == player && feld[3][2] == player && feld[4][3] == player && feld[5][4] == player) {
		return player;
	}
	if(feld[4][0] == player && feld[3][1] == player && feld[2][2] == player && feld[1][3] == player && feld[0][4] == player) {
		return player;
	}
	if(feld[5][1] == player && feld[4][2] == player && feld[3][3] == player && feld[2][4] == player && feld[1][5] == player) {
			return player;
	}
	//feld suche (farben)
	int farben[6][6] = {
		{1,1,2,5,6,6},
		{1,2,3,4,5,6},
		{2,3,3,4,4,5},
		{8,9,9,10,10,11},
		{7,8,9,10,11,12},
		{7,7,8,11,12,12}
	};
	int eins = 0;
	int zwei = 0;
	int drei = 0;
	int vier = 0;
	int fuenf = 0;
	int sechs = 0;
	int sieben = 0;
	int acht = 0;
	int neun = 0;
	int zehn = 0;
	int elf = 0;
	int zwoelf = 0;
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			if(feld[i][j] == player) {
				if(farben[i][j] == 1) {
					eins++;
				}
				if(farben[i][j] == 2) {
					zwei++;
				}
				if(farben[i][j] == 3) {
					drei++;
				}
				if(farben[i][j] == 4) {
					vier++;
				}
				if(farben[i][j] == 5) {
					fuenf++;
				}
				if(farben[i][j] == 6) {
					sechs++;
				}
				if(farben[i][j] == 7) {
					sieben++;
				}
				if(farben[i][j] == 8) {
					acht++;
				}
				if(farben[i][j] == 9) {
					neun++;
				}
				if(farben[i][j] == 10) {
					zehn++;
				}
				if(farben[i][j] == 11) {
					elf++;
				}
				if(farben[i][j] == 12) {
					zwoelf++;
				}
				
			}
		}
	}
	if(eins == 3 || zwei == 3 || drei == 3 || vier == 3 || fuenf == 3 || sechs == 3 || sieben == 3 || acht == 3 || neun == 3 || zehn == 3 || elf == 3 || zwoelf == 3) {
		return player;
	}
	//viererblock
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			if(feld[i][j] == player && feld[i + 1][j] == player && feld[i][j + 1] == player && feld[i + 1][j + 1] == player) {
				return player;
			}
		}
	}
	//kein sieg
	return 0;
}