#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<Windows.h>

#include"all_about.h"

#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int time;
} PlayerData;


// 비교 함수(순위표 계산)
int compare(const void* a, const void* b) {
    const PlayerData* playerA = (const PlayerData*)a;
    const PlayerData* playerB = (const PlayerData*)b;

    return playerA->time - playerB->time;
}

void Ranking_table() {
    FILE* fp = fopen("timer.txt", "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    PlayerData players[MAX_ENTRIES];
    int numEntries = 0;

    char line[MAX_NAME_LENGTH + 10];
    char name[MAX_NAME_LENGTH];
    int time;

    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%s", name);
        if (fgets(line, sizeof(line), fp) != NULL) {
            sscanf(line, "%d", &time);
            strncpy(players[numEntries].name, name, MAX_NAME_LENGTH);
            players[numEntries].time = time;
            numEntries++;
        }

        if (numEntries >= MAX_ENTRIES) {
            printf("\t\t최대 엔트리 수를 초과했습니다.\n");
            break;
        }
    }
    text_color(LIGHTGREEN, BLACK);
    fclose(fp);

    qsort(players, numEntries, sizeof(PlayerData), compare);
    printf("\t\t\n");

    printf("\t\t\t| |\t _ \t______                _     \t _ \t| |\n");
    printf("\t\t\t| |\t| |\t| ___ \\              | |    \t| |\t| |\n");
    printf("\t\t\t| |\t| |\t| |_/ /  __ _  _ __  | | __ \t| |\t| |\n");
    printf("\t\t\t| |\t| |\t|    /  / _` || '_ \\ | |/ / \t| |\t| |\n");
    printf("\t\t\t| |\t|_|\t| |\\ \\ | (_| || | | ||   <  \t|_|\t| |\n");
    printf("\t\t\t| |\t(_)\t\\_| \\_| \\__,_||_| |_||_|\\_\\ \t(_)\t| |\n");



    int numPrinted = 0;
    for (int i = 0; i < numEntries && numPrinted < 3; i++) {
        int minutes = players[i].time / 60; // 초를 분으로 변환
        int seconds = players[i].time % 60; // 초 단위 계산
        printf("\t\t\t| |\t\t\t\t\t\t\t| |\n");
        printf("\t\t\t| |\t-------------------%d위-------------------\t| |\n\t\t\t| |\t\t\t\t\t\t\t| |\n", i + 1);
        printf("\t\t\t| |\t%d위 => 닉네임: %s\t, 시간: %d분 %d초\t\t| |\n", numPrinted + 1, players[i].name, minutes, seconds);
        numPrinted++;
    }
    printf("\t\t\t___________________________________________________________");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
