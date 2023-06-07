#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define SIZE 10 //명예의 전당 크기
#define ROW 32 //미로 크기
#define COL 32
#define Max_id_size 20

int game_menu();
void game_rule();
void game_start(int stage);
void game_story(int story);
void game_timer(int stage);
int packman_create(int x, int y);
void packman_remove(int x, int y);
int ch_move(int stage);
void ghost_create(int x, int y);
void ghost_remove(int x, int y);
void maze();
void create_maze();
void maze_set();
void print_maze();
int check_block(int x, int y); //좌표를 입력받고 그걸로 확인 (임의)
bool clear(int stage, int playing);
void choose_random_location(int* width, int* length);
void gold_item();
int bgm();
void image_add();
void display(int x, int y);
void clear_time();
void rank();
void gotoxy(int x, int y);
void setConsoleColor(int colorCode);
void showAndHideText(char* text);

clock_t start, end;  // 전역 변수로 선언
int item_width, item_length;
int p_x, p_y; //팩맨의 x좌표와 y좌표
int g_x, g_y; //고스트의 x좌표와 y좌표
int stage = 1;
int ghost_movement = 0;
int playing;
int maze_str[ROW][COL]; //maze라는 함수가 있어서 이름 변경
int d_x, d_y; //목적지 위치 destination_x 여기다가 랜덤생성된 좌표를 입력해주세요
int key_inven; //열쇠 먹으면 이 변수 1로 해주세요
int t_x = 33, t_y = 33; //텍스트의 x좌표와 y좌표(미정)

//팩맨의 생성
int packman_create(int x, int y) {
    gotoxy(x, y);
    printf("(팩맨)");
    return 1;
}

//팩맨 삭제
void packman_remove(int x, int y) {
    gotoxy(x, y);
    printf("\0");
}

//팩맨의 움직임 + 고스트의 움직임
int ch_move(int stage) {
     //스테이지가 넘어갈때 초기화
    int key;
     //게임이 실행되는 동안에만 반복
        scanf("%d", &key);
        if (key == 77) { //입력한 키와 오른쪽 키의 아스키 코드가 같다면
            if (check_block(p_x + 1, p_y)) //벽의 좌표와 자신의 좌표를 비교해 같다면
            {
                showAndHideText("벽이 있는 방향으로는 움직일 수 없다.");
                return 0;
            }
            packman_remove(p_x, p_y); //원래자리에 있던 팩맨 삭제
            gotoxy(p_x + 1, p_y); //오른쪽으로 한칸
            packman_create(p_x, p_y); //새로운 자리에 팩맨 출력
            ghost_movement++;
        }

        else if (key == 75) {
            if (check_block(p_x - 1, p_y)) {
                showAndHideText("벽이 있는 방향으로는 움직일 수 없다.");
                return 0;
            }
            packman_remove(p_x, p_y); //현재위치?
            gotoxy(p_x - 1, p_y); //왼쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }

        else if (key == 72) {
            if (check_block(p_x, p_y + 1)) {
                showAndHideText("벽이 있는 방향으로는 움직일 수 없다.");
                return 0;
            }
            packman_remove(p_x, p_y);
            gotoxy(p_x, p_y + 1); //오른쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }
        else if (key == 80) {
            if (check_block(p_x, p_y - 1)) {
                showAndHideText("벽이 있는 방향으로는 움직일 수 없다.");
                return 0;
            }
            packman_remove(p_x, p_y);
            gotoxy(p_x, p_y - 1); //오른쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }
        if (ghost_movement % 3 == 0) //3번 증가하면 작동
             //아마 큐나 스택 사용
    
}

//고스트 생성
void ghost_create(int x, int y) {
    gotoxy(x, y);
    printf("(호박)");
}

//팩맨 삭제
void ghost_remove(int x, int y) {
    gotoxy(x, y);
    printf("\0");
}