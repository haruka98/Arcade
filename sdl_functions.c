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

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//Loads individual image
SDL_Surface* loadSurface(char* path);
//Loads individual image as texture
SDL_Texture* loadTexture(char* path);
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
//Current displayed texture
SDL_Texture* gTexture = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;
//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

void render() {
	SDL_RenderPresent(gRenderer);
}
void clear_render() {
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(gRenderer);
}
void spiel_menu_render() {
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/spiel_menu.bmp");
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	SDL_BlitSurface(img, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface(gWindow);
	SDL_FreeSurface(img);
	
}
void spiel_menu_render_qango() {
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/spiel_menu_qango.bmp");
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	SDL_BlitSurface(img, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface(gWindow);
	SDL_FreeSurface(img);
	
}
void spiel_menu_render_tron() {
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/spiel_menu_tron.bmp");
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	SDL_BlitSurface(img, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface(gWindow);
	SDL_FreeSurface(img);
	
}
void spiel_menu_render_tictactoe() {
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/spiel_menu_tictactoe.bmp");
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	SDL_BlitSurface(img, NULL, gScreenSurface, NULL );
	SDL_UpdateWindowSurface(gWindow);
	SDL_FreeSurface(img);
	
}
void render_menue() {
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	//Oberer Menüpunkt
	if(x < 550 && x > 250 && y < 275 && y > 245) {
		SDL_Rect fillRect1 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15 - 30 - 10, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xD4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
	} else {
		SDL_Rect fillRect1 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15 - 30 - 10, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xF4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
	}
	//Mittlerer Menüpunkt
	if(x < 550 && x > 250 && y < 315 && y > 285) {
		SDL_Rect fillRect2 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xD4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
	} else {
		SDL_Rect fillRect2 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xF4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
	}
	//Unterer Menüpunkt (Beenden)
	if(x < 550 && x > 250 && y < 355 && y > 325) {
		SDL_Rect fillRect3 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15 + 30 + 10, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xD4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect3);
	} else {
		SDL_Rect fillRect3 = {(SCREEN_WIDTH / 2) - 150, (SCREEN_HEIGHT / 2) - 15 + 30 + 10, 300, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xF4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect3);
	}
	//Render Text
	render_text("Spiel starten", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 40, 20, 1, 0);
	render_text("Einstellungen", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 20, 1, 0);
	render_text("Beenden", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 40, 20, 1, 0);
}

SDL_Color nCol(int r, int g, int b){
	SDL_Color col={r,g,b};
	return col;
}
void render_text(char* text, int x, int y, int size, int center, int farbe) {
	TTF_Font* font = TTF_OpenFont("arial.ttf", size);
	SDL_Color color = {255, 255, 255};
	if(farbe == 1) {
		color = nCol(0, 0, 0);
	}
	SDL_Surface* surfaceMessage = TTF_RenderUTF8_Blended(font, text, color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); //convert into texture
	int w = 0;
	int h = 0;
	SDL_QueryTexture(Message, NULL, NULL, &w, &h);	//Größe bestimmen
	SDL_Rect Message_rect;
	if(center == 1) {
		x = x - (w / 2);
		y = y - (h / 2);
	}
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = w;
	Message_rect.h = h;
	
	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	//SDL_RenderPresent(gRenderer);		//Benötigt zu viel Leistung
	SDL_FreeSurface(surfaceMessage);	//Fix für die verschwindene Schrift
	SDL_DestroyTexture(Message);
	TTF_CloseFont(font);
}
void render_settings(int speed_tron) {
	int x = 0;
	int y = 0;
	SDL_GetMouseState(&x, &y);
	//Zurück (Hauptmenü)
	if(x < 110 && x > 30 && y < 570 && y > 540) {
		SDL_Rect fillRect1 = {30, SCREEN_HEIGHT - 60, 80, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xD4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
	} else {
		SDL_Rect fillRect1 = {30, SCREEN_HEIGHT - 60, 80, 30};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xF4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect1);
	}
	if(x < SCREEN_WIDTH / 2 + 250 && x > SCREEN_WIDTH / 2 - 250 && y < SCREEN_HEIGHT / 2 + 25 - 50 && y > SCREEN_HEIGHT / 2 - 25 - 50) {
		SDL_Rect fillRect2 = {SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 25 - 50, 500, 50};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xD4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
	} else {
		SDL_Rect fillRect2 = {SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 25 - 50, 500, 50};
		SDL_SetRenderDrawColor(gRenderer, 0x1D, 0x57, 0xF4, 0xFF);
		SDL_RenderFillRect(gRenderer, &fillRect2);
	}
	if(speed_tron == 10) {
		render_text("Speed Tron: NORMAL", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 20, 1, 0);
	}
	if(speed_tron == 5) {
		render_text("Speed Tron: SCHNELL", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 20, 1, 0);
	}
	if(speed_tron == 15) {
		render_text("Speed Tron: LANGSAM", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 20, 1, 0);
	}
	if(speed_tron == 1) {
		render_text("Speed Tron: SEHR SCHNELL", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 20, 1, 0);
	}
	if(speed_tron == 20) {
		render_text("Speed Tron: SEHR LANGSAM", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 20, 1, 0);
	}
	render_text("Einstellungen", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 275, 30, 1, 1);
	render_text("Zurück", 30 + (80 / 2), SCREEN_HEIGHT - 60 + (30 / 2), 20, 1, 0);
}

void render_qango_field() {
	SDL_Rect fillRect1 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect1);
	
	SDL_Rect fillRect2 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect2);
	
	SDL_Rect fillRect3 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect3);
	
	SDL_Rect fillRect4 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect4);
	
	SDL_Rect fillRect5 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect5);
	
	SDL_Rect fillRect6 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) - 180, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect6);
	
	SDL_Rect fillRect7 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect7);
	
	SDL_Rect fillRect8 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect8);
	
	SDL_Rect fillRect9 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect9);
	
	SDL_Rect fillRect10 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect10);
	
	SDL_Rect fillRect11 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect11);
	
	SDL_Rect fillRect12 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) - 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect12);
	
	SDL_Rect fillRect13 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect13);
	
	SDL_Rect fillRect14 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect14);
	
	SDL_Rect fillRect15 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect15);
	
	SDL_Rect fillRect16 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect16);
	
	SDL_Rect fillRect17 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect17);
	
	SDL_Rect fillRect18 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) - 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect18);
	
	SDL_Rect fillRect19 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect19);
	
	SDL_Rect fillRect20 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect20);
	
	SDL_Rect fillRect21 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect21);
	
	SDL_Rect fillRect22 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect22);
	
	SDL_Rect fillRect23 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect23);
	
	SDL_Rect fillRect24 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) - 00, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect24);
	
	SDL_Rect fillRect25 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect25);
	
	SDL_Rect fillRect26 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect26);
	
	SDL_Rect fillRect27 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x69, 0xE2, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect27);
	
	SDL_Rect fillRect28 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0x71, 0xC1, 0x51, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect28);
	
	SDL_Rect fillRect29 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect29);
	
	SDL_Rect fillRect30 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) + 60, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect30);
	
	SDL_Rect fillRect31 = {(SCREEN_WIDTH / 2) - 180, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect31);
	
	SDL_Rect fillRect32 = {(SCREEN_WIDTH / 2) - 120, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect32);
	
	SDL_Rect fillRect33 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x9C, 0x32, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect33);
	
	SDL_Rect fillRect34 = {(SCREEN_WIDTH / 2) - 00, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF4, 0xF1, 0x22, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect34);
	
	SDL_Rect fillRect35 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect35);
	
	SDL_Rect fillRect36 = {(SCREEN_WIDTH / 2) + 120, (SCREEN_HEIGHT / 2) + 120, 60, 60};
	SDL_SetRenderDrawColor(gRenderer, 0xF2, 0x4B, 0xDB, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect36);
	
}
void render_qango_fig(int feld[6][6]) {
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			//feld durchgehen
			if(feld[i][j] == 1) {
				SDL_Rect fillRect = {(SCREEN_WIDTH / 2) - 180 + 15 + i * 60, (SCREEN_HEIGHT / 2) - 180 + 15 + j * 60, 30, 30};
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);
				//SDL_RenderCopy(gRenderer, NULL, NULL, &rect);
			}
			if(feld[i][j] == 2) {
				SDL_Rect fillRect = {(SCREEN_WIDTH / 2) - 180 + 15 + i * 60, (SCREEN_HEIGHT / 2) - 180 + 15 + j * 60, 30, 30};
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);
				//SDL_RenderCopy(gRenderer, NULL, NULL, &rect);
			}
		}
	}
}
void render_qango_player(char* player) {
	render_text(player, (SCREEN_WIDTH / 2), 45, 40, 1, 1);
}
void render_tron(int spielfeld[60][80]) {
	for(int i = 0; i < 60; i++) {
		for(int j = 0; j < 80; j++) {
			if(spielfeld[i][j] == 1) {
				SDL_Rect fillRect = {j * 10, i * 10, 10, 10};
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x55, 0xFF, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);
			}
			if(spielfeld[i][j] == 2) {
				SDL_Rect fillRect2 = {j * 10, i * 10, 10, 10};
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x55, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect2);
			}
		}
	}
}
void render_tron_spitze(int x, int y, int special) {
	SDL_Rect fillRect = {2 + x * 10, 2 + y * 10, 6, 6};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);
	if(special == 1) {
		SDL_Surface* imgr = NULL;
		SDL_Texture* texture = NULL;
		SDL_Rect pos;
		pos.x = 2 + x * 10 - 25;
		pos.y = 2 + y * 10 - 25;
		pos.w = 50;
		pos.h = 50;
		imgr = SDL_LoadBMP("img/r.bmp");
		texture = SDL_CreateTextureFromSurface(gRenderer, imgr);
		SDL_RenderCopy(gRenderer, texture, NULL, &pos);
		SDL_FreeSurface(imgr);
		SDL_DestroyTexture(texture);
	}
}
void render_background(int special) {
	if(special == 1) {
		SDL_Surface* imgr = NULL;
		SDL_Texture* texture = NULL;
		SDL_Rect pos;
		pos.x = SCREEN_WIDTH / 2 - 250;
		pos.y = SCREEN_HEIGHT / 2 - 250;
		pos.w = 500;
		pos.h = 500;
		imgr = SDL_LoadBMP("img/r.bmp");
		texture = SDL_CreateTextureFromSurface(gRenderer, imgr);
		SDL_RenderCopy(gRenderer, texture, NULL, &pos);
		SDL_FreeSurface(imgr);
		SDL_DestroyTexture(texture);
	}
}
void render_tictactoe(int feld[3][3], int special) {
	SDL_Rect fillRect1 = {(SCREEN_WIDTH / 2) - 180 - 2, (SCREEN_HEIGHT / 2) - 180 - 2, 120 + 2, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect1);
	
	SDL_Rect fillRect1b = {(SCREEN_WIDTH / 2) - 180 + 2, (SCREEN_HEIGHT / 2) - 180 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect1b);
	
	SDL_Rect fillRect2 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 180 - 2, 120, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect2);
	
	SDL_Rect fillRect2b = {(SCREEN_WIDTH / 2) - 60 + 2, (SCREEN_HEIGHT / 2) - 180 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect2b);
	
	SDL_Rect fillRect3 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 180 - 2, 120 + 2, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect3);
	
	SDL_Rect fillRect3b = {(SCREEN_WIDTH / 2) + 60 + 2, (SCREEN_HEIGHT / 2) - 180 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect3b);
	
	SDL_Rect fillRect4 = {(SCREEN_WIDTH / 2) - 180 - 2, (SCREEN_HEIGHT / 2) - 60, 120 + 2, 120};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect4);
	
	SDL_Rect fillRect4b = {(SCREEN_WIDTH / 2) - 180 + 2, (SCREEN_HEIGHT / 2) - 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect4b);
	
	SDL_Rect fillRect5 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) - 60, 120, 120};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect5);
	
	SDL_Rect fillRect5b = {(SCREEN_WIDTH / 2) - 60 + 2, (SCREEN_HEIGHT / 2) - 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect5b);
	
	SDL_Rect fillRect6 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) - 60, 120 + 2, 120};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect6);
	
	SDL_Rect fillRect6b = {(SCREEN_WIDTH / 2) + 60 + 2, (SCREEN_HEIGHT / 2) - 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect6b);
	
	SDL_Rect fillRect7 = {(SCREEN_WIDTH / 2) - 180 - 2, (SCREEN_HEIGHT / 2) + 60, 120 + 2, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect7);
	
	SDL_Rect fillRect7b = {(SCREEN_WIDTH / 2) - 180 + 2, (SCREEN_HEIGHT / 2) + 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect7b);
	
	SDL_Rect fillRect8 = {(SCREEN_WIDTH / 2) - 60, (SCREEN_HEIGHT / 2) + 60, 120, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect8);
	
	SDL_Rect fillRect8b = {(SCREEN_WIDTH / 2) - 60 + 2, (SCREEN_HEIGHT / 2) + 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect8b);
	
	SDL_Rect fillRect9 = {(SCREEN_WIDTH / 2) + 60, (SCREEN_HEIGHT / 2) + 60, 120 + 2, 120 + 2};
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect9);
	
	SDL_Rect fillRect9b = {(SCREEN_WIDTH / 2) + 60 + 2, (SCREEN_HEIGHT / 2) + 60 + 2, 116, 116};
	SDL_SetRenderDrawColor(gRenderer, 0xE8, 0xE8, 0xE8, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect9b);
	//Spieler eingaben
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(feld[j][i] == 2) {
				if(special == 1) {
					SDL_Surface* imgr = NULL;
					SDL_Texture* texture = NULL;
					SDL_Rect pos;
					pos.x = (SCREEN_WIDTH / 2) - 180 + 10 + j * 120;
					pos.y = (SCREEN_HEIGHT / 2) - 180 + 10 + i * 120;
					pos.w = 90;
					pos.h = 90;
					imgr = SDL_LoadBMP("img/r.bmp");
					texture = SDL_CreateTextureFromSurface(gRenderer, imgr);
					SDL_RenderCopy(gRenderer, texture, NULL, &pos);
					SDL_FreeSurface(imgr);
					SDL_DestroyTexture(texture);
				} else {
					render_circle((SCREEN_WIDTH / 2) - 180 + 2 + (116 / 2) + j * 120, (SCREEN_HEIGHT / 2) - 180 + 2 + (116 / 2) + i * 120, 45);
				}
			}
			if(feld[j][i] == 1) {
				render_cross((SCREEN_WIDTH / 2) - 180 + 2 + (116 / 2) + j * 120, (SCREEN_HEIGHT / 2) - 180 + 2 + (116 / 2) + i * 120, 45);
			}
		}
	}
}
void render_cross(int x, int y, int radius) {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF );
	for(int i = 0; i < radius * 2; i++) {
		SDL_RenderDrawPoint(gRenderer, x - radius + i, y - radius + i);
	}
	for(int i = 0; i < radius * 2; i++) {
		SDL_RenderDrawPoint(gRenderer, x + radius - i, y - radius + i);
	}
}
void render_circle(int x, int y, int radius) {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF );
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int a = 0;
	int b = radius;
	SDL_RenderDrawPoint(gRenderer, x, y + radius);
	SDL_RenderDrawPoint(gRenderer, x, y - radius);
	SDL_RenderDrawPoint(gRenderer, x + radius, y);
	SDL_RenderDrawPoint(gRenderer, x - radius, y);
	while(a < b) {
		if(f >= 0) {
			b--;
			ddF_y += 2;
			f += ddF_y;
		}
		a++;
		ddF_x = ddF_x + 2;
		f = f + ddF_x + 1;
		SDL_RenderDrawPoint(gRenderer, x + a, y + b);
		SDL_RenderDrawPoint(gRenderer, x - a, y + b);
		SDL_RenderDrawPoint(gRenderer, x + a, y - b);
		SDL_RenderDrawPoint(gRenderer, x - a, y - b);
		SDL_RenderDrawPoint(gRenderer, x + b, y + a);
		SDL_RenderDrawPoint(gRenderer, x - b, y + a);
		SDL_RenderDrawPoint(gRenderer, x + b, y - a);
		SDL_RenderDrawPoint(gRenderer, x - b, y - a);
	}
}
void tron_help() {
	SDL_Window* gWindow2 = NULL;
	SDL_Renderer* gRenderer2 = NULL;
	SDL_Texture* gTexture2 = NULL;
	SDL_Surface* gScreenSurface2 = NULL;
	gWindow2 = SDL_CreateWindow("Tron - Help", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* icon = IMG_Load("img/ico.bmp");
	SDL_SetWindowIcon(gWindow2, icon);
	SDL_FreeSurface(icon);
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/help_1_tron.bmp");
	gScreenSurface2 = SDL_GetWindowSurface(gWindow2);
	SDL_BlitSurface(img, NULL, gScreenSurface2, NULL );
	SDL_UpdateWindowSurface(gWindow2);
	SDL_FreeSurface(img);
	
	SDL_Event event;
	int exit = 0;
	while(exit == 0) {
		SDL_PollEvent(&event);
		if(event.key.keysym.sym == SDLK_ESCAPE) {
			exit = 1;
		}
	}
	
	SDL_DestroyRenderer(gRenderer2);
	SDL_DestroyWindow(gWindow2);
	gWindow2 = NULL;
	gRenderer2 = NULL;
}
void tictactoe_help() {
	SDL_Window* gWindow2 = NULL;
	SDL_Renderer* gRenderer2 = NULL;
	SDL_Texture* gTexture2 = NULL;
	SDL_Surface* gScreenSurface2 = NULL;
	gWindow2 = SDL_CreateWindow("TicTacToe - Help", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* icon = IMG_Load("img/ico.bmp");
	SDL_SetWindowIcon(gWindow2, icon);
	SDL_FreeSurface(icon);
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/help_1_tictactoe.bmp");
	gScreenSurface2 = SDL_GetWindowSurface(gWindow2);
	SDL_BlitSurface(img, NULL, gScreenSurface2, NULL );
	SDL_UpdateWindowSurface(gWindow2);
	SDL_FreeSurface(img);
	
	SDL_Event event;
	int exit = 0;
	while(exit == 0) {
		SDL_PollEvent(&event);
		if(event.key.keysym.sym == SDLK_ESCAPE) {
			exit = 1;
		}
	}
	
	SDL_DestroyRenderer(gRenderer2);
	SDL_DestroyWindow(gWindow2);
	gWindow2 = NULL;
	gRenderer2 = NULL;
}
void qango_help() {
	SDL_Window* gWindow2 = NULL;
	SDL_Renderer* gRenderer2 = NULL;
	SDL_Texture* gTexture2 = NULL;
	SDL_Surface* gScreenSurface2 = NULL;
	gWindow2 = SDL_CreateWindow("Qango - Help", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface* icon = IMG_Load("img/ico.bmp");
	SDL_SetWindowIcon(gWindow2, icon);
	SDL_FreeSurface(icon);
	SDL_Surface* img = NULL;
	img = SDL_LoadBMP("img/help_1_qango.bmp");
	gScreenSurface2 = SDL_GetWindowSurface(gWindow2);
	SDL_BlitSurface(img, NULL, gScreenSurface2, NULL );
	SDL_UpdateWindowSurface(gWindow2);
	SDL_FreeSurface(img);
	
	SDL_Event event;
	int exit = 0;
	while(exit == 0) {
		SDL_PollEvent(&event);
		if(event.key.keysym.sym == SDLK_ESCAPE) {
			exit = 1;
		}
	}
	
	SDL_DestroyRenderer(gRenderer2);
	SDL_DestroyWindow(gWindow2);
	gWindow2 = NULL;
	gRenderer2 = NULL;
}
int init_sdl(char* window_name) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return 1;
	} else {
		TTF_Init();
		gWindow = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		SDL_Surface* icon = IMG_Load("img/ico.bmp");
		SDL_SetWindowIcon(gWindow, icon);
		SDL_FreeSurface(icon);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return 2;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 4;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return 5;
				}
			}
		}
	}
	return 0;
}

int close_sdl() {
	for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(char* path) {
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	return loadedSurface;
}
SDL_Texture* loadTexture(char* path) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	} else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

int loadMedia_sdl(char* path) {
    if(strcmp(path, "0") == 0) {
		
	} else {
		//Load PNG texture
		gTexture = loadTexture(path);
		if( gTexture == NULL ) {
			printf("Failed to load texture image!\n");
			return 1;
		}
	}
	return 0;
}
