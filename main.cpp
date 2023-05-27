
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SIZE 10 //명예의 전당 크기
#define ROW 32 //미로 크기
#define COL 32
#define Max_id_size 20
#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 100

int game_menu();
void game_rule();
void game_start(int stage);
void game_story(int story);
void game_timer(int stage);
int packman_create(int x, int y);
void packman_remove(int x, int y);
void ch_move(int stage);
void ghost_create(int x, int y);
void ghost_remove(int x, int y);
void maze();
void create_maze();
void maze_set();
void print_maze();
int check_block(int x,int y); //좌표를 입력받고 그걸로 확인 (임의)
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
void Ranking_table();
void main_maze();

clock_t start, end;  // 전역 변수로 선언
int item_width, item_length;
int p_x, p_y; //팩맨의 x좌표와 y좌표
int g_x, g_y; //고스트의 x좌표와 y좌표
int stage = 1;
int ghost_movement=0;
int playing;
int maze_str[ROW][COL]; //maze라는 함수가 있어서 이름 변경
int d_x,d_y; //목적지 위치 destination_x 여기다가 랜덤생성된 좌표를 입력해주세요
int key_inven; //열쇠 먹으면 이 변수 1로 해주세요
int t_x = 33, t_y = 33; //텍스트의 x좌표와 y좌표(미정)
int choice;

//메인 함수
int main() {
    int stage = 1;
    game_menu();
    PlaySound(TEXT("C:\\maze.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    //중간 게임실행 코드
    PlaySound(NULL, NULL, SND_ASYNC);

    system("cls");// 게임메뉴 화면 안보이게
    game_story(1);
    system("cls");//스토리 지워지게
    
    //공포이미지 출력
    printf("게임시작");
    getchar();
    image_add();

    if (stage == 1) {
        game_start(1);//이 함수가 돌아가는동안 밑에 실행 안되나? 물어보기.
        ch_move(1);
        if (clear(1, playing)) {
            system("cls"); //현재 있는 미로 삭제
            end=clock();
            game_timer(stage);
            stage++;
            game_story(2);
        }
    }
    if (stage == 2) {
        game_start(2);
        ch_move(2);
        if (clear(2,playing)) {
            system("cls");
            game_story(3);
            system("cls");
            end=clock();
            game_timer(stage); //파일에 저장도 포함
            clear_time(); //클리어시간 보여주기
            Ranking_table();
            printf("나가기를 원한다면 e를 눌러주세요: ");
            scanf("%c",&choice);
            if (choice=='e'||choice=='E'){
                printf("3초후 메인화면으로 돌아갑니다.");
                Sleep(3000);
                system("cls");
                game_menu();
            }
        }
    }
return 0;
}
