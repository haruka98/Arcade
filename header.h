int qango();
int spiel_menu(int speed_tron, int special);
void spiel_menu_render();
void spiel_menu_render_qango();
void spiel_menu_render_tron();
void spiel_menu_render_tictactoe();
void render_background(int special);
int tron(int speed, int special);
void render_tron(int spielfeld[60][80]);
void render_tron_spitze(int x, int y, int special);
int tictactoe(int special);
void render_tictactoe(int feld[3][3], int special);
void render_circle(int x, int y, int radius);
void render_cross(int x, int y, int radius);

int init_sdl(char* window_name);
int close_sdl();
SDL_Surface* loadSurface(char* path);
SDL_Texture* loadTexture(char* path);
int loadMedia_sdl(char* path);
char* addstring(char* str1, char* str2);

void render();
void clear_render();

void render_menue();
void render_settings(int speed_tron);
void render_text(char* text, int x, int y, int size, int center, int farbe);
void render_qango_field();
void render_qango_player(char* player);
int test_qango(int feld[6][6], int player);
void render_qango_fig(int feld[6][6]);
int nullen_qango(int feld[6][6]);

void tron_help();
void tictactoe_help();
void qango_help();