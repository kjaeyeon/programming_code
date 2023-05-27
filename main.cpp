
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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

//게임 메뉴
int game_menu() {
    int stage = 1; //메뉴를 불러올때마다 1스테이지부터 시작
    while (1) {
        if ()//start를 누른다면
            return 0; //메뉴나가기}
        else if () //rule을 누른다면
            game_rule(); //rule 불러오기
        else if () //나가기를 누른다면
            exit(1); //나가기
    }
}

//게임 시작 화면
void game_start(int stage) {
    switch (stage) //입력받은 스테이지가 2라면 전부 실행, 1이면 defalut값만 실행
        case 2: gold_item();
    defalut:
        maze();
        start=clock(); //함수 위치가 다른곳인데도 실행이 되는지 확인
        playing = 1;
}
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
void ch_move(int stage) {
    int ghost_movement = 0; //스테이지가 넘어갈때 초기화
    int key;
    while (playing==1){ //게임이 실행되는 동안에만 반복
        scanf("%d", &key);
        if (key == 77) { //입력한 키와 오른쪽 키의 아스키 코드가 같다면
            if (check_block(p_x + 1, p_y)) //벽의 좌표와 자신의 좌표를 비교해 같다면
                continue;
            packman_remove(p_x, p_y);
            gotoxy(p_x + 1, p_y); //오른쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }

        else if (key == 75) {
            if (check_block(p_x - 1, p_y)) //벽의 좌표와 자신의 좌표를 비교해 같다면
                continue;
            packman_remove(p_x, p_y); //현재위치?
            gotoxy(p_x - 1, p_y); //왼쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }

        else if (key == 72) {
            if (check_block(p_x, p_y + 1)) //벽의 좌표와 자신의 좌표를 비교해 같다면
                continue;
            packman_remove(p_x, p_y);
            gotoxy(p_x, p_y + 1); //오른쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }
        else if (key == 80) {
            if (check_block(p_x, p_y - 1)) //벽의 좌표와 자신의 좌표를 비교해 같다면
                continue;
            packman_remove(p_x, p_y);
            gotoxy(p_x, p_y - 1); //오른쪽으로 한칸
            packman_create(p_x, p_y);
            ghost_movement++;
        }
        if (ghost_movement % 3 == 0) //3번 증가하면 작동
            팩맨이 있는 방향으로 1칸 움직이기; //아마 큐나 스택 사용
    }
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
    image_add();
    Sleep(2000); //사진을 2초동안 보여줌
    system("cls");
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
            sortStageClearTime(); //오름차순으로 시간 정렬
            rank(); //파일에 있는 내용을 배열로 불러와 크기를 비교하여 3개 순위 출력하기(만약에 가능하다면 현재 자기 순위나 상위 몇%인지 표시(심화))
            if (나가기를 누른다면){
                system("cls");
                game_menu();
            }
        }
    }
}
