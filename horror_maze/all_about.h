#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 


void Ranking_table();
int game_menu();
void game_story(int stage, int clear);
void image_add();
void gotoxy(int x, int y);
void SetConsoleView();
void setConsoleColor(int colorCode);
void maze1_main();
void maze2_main();
void text_color(int foreground, int backgrond);
