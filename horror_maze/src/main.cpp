#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<conio.h>
#include <windows.h>
#include <string.h>
#include <mmsystem.h>
#include"all_about.h"
#pragma comment(lib, "winmm.lib")

#define SIZE 31// 미로의 크기

int maze[SIZE][SIZE];
int distance[SIZE][SIZE];   // 시작점으로부터의 거리를 저장하기 위한 배열
extern int stage;
extern int clear;
double start_time1, end_time1;
double start_time2, end_time2;
double time1 = 0, time2 = 0;
void move_enemy(int* enemyX, int* enemyY, int p_x, int p_y);
int calculate_distance(int startX, int startY, int targetX, int targetY);


//타이머 계산
void game_timer(int stage) {

    int stage1_time, stage2_time, total_time;
    int min, sec;
    if (stage == 1) {
        stage1_time = 0;
        min = 0, sec = 0;
        stage1_time = difftime(end_time1, start_time1);
        min = stage1_time / 60;
        sec = stage1_time % 60;
        printf("\t\t1스테이지 플레이 시간: %d분 %d초\n", min, sec);
        time1 = stage1_time;
    }
    if (stage == 2) {
        stage2_time = 0;
        min = 0, sec = 0;
        stage2_time = difftime(end_time2, start_time2);
        min = stage2_time / 60;
        sec = stage2_time % 60;
        printf("\t\t2스테이지 플레이 시간: %d분 %d초 \n", min, sec);
        time2 = stage2_time;
    }
    if (clear == 2) {
        total_time = 0;
        total_time = time1 + time2;

        // 사용자 아이디 입력 받기
        char user_id[20];
        printf("\t\t사용자 아이디를 입력하세요: ");
        scanf("%s", user_id);

        // 파일에 총 시간 저장
        FILE* fp = fopen("timer.txt", "a");
        if (fp != NULL) {
            fprintf(fp, "%s\n", user_id);
            fprintf(fp, "%d\n", total_time);
            fclose(fp);
        }
        else {
            printf("\t\t파일을 열 수 없습니다.\n");
        }
    }
}



int main() {
    SetConsoleView();
    PlaySound(TEXT("C:\\Users\\jsn30\\OneDrive\\바탕 화면\\3조 미로찾기\\CNJ_MAZE\\CNJ_MAZE\\maze.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    while (1) {
        game_menu();
        game_story(stage, clear);
        start_time1 = time(NULL);
        maze1_main();
        end_time1 = time(NULL);
        game_timer(stage);
        if (clear == 1) stage++;
        Sleep(2500);
        system("cls");
        if (stage == 2) {
            game_story(stage, clear);
            start_time2 = time(NULL);
            maze2_main();
            end_time2 = time(NULL);
            game_timer(stage);
            stage++;
            Sleep(2500);
        }

        if (clear == 2) {
            system("cls");

            game_story(stage, clear);
            system("cls");
            Ranking_table();
            getch();
        }
        stage = 1;
        clear = 0;
    }
    PlaySound(NULL, NULL, SND_ASYNC);
    return 0;
}
