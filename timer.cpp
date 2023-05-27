#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_ENTRIES 100
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

// 타이머
time_t start_time, end_time;  // 전역 변수로 선언

void game_timer(int stage) {
    double stage1_time = 0, stage2_time = 0;

    switch (stage) {
    case 1:
        //(stage1)
        start_time = time(NULL);
        end_time = time(NULL);
        stage1_time = difftime(end_time, start_time);
        break;
    case 2:
        //(stage2)
        start_time = time(NULL);
        end_time = time(NULL);
        stage2_time = difftime(end_time, start_time);
        break;
    default:
        printf("유효하지 않은 스테이지입니다.\n");
        return;
    }

    //(총 시간)
    double total_time = stage1_time + stage2_time;
    printf("%.2f\n", total_time);

    // 사용자 아이디 입력 받기
    char user_id[20];
    printf("사용자 아이디를 입력하세요: ");
    scanf("%s", user_id);

    // 파일에 총 시간 저장
    FILE* fp = fopen("timer.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%s\n", user_id);
        fprintf(fp, "%.2f\n", total_time);
        fclose(fp);
    }
    else {
        printf("파일을 열 수 없습니다.\n");
    }

    // total_time을 보여주기 위해 사용자 입력 대기
    printf("아무 키나 누르세요...\n");
    while (getchar() != '\n') {}  // Enter 키까지 입력 대기
}


//게임 클리어 후 닉네임과 걸린 시간 출력
void Print_timer() {
    FILE* file = fopen("timer.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    char recentName[MAX_NAME_LENGTH];
    int recentTime = 0;

    char name[MAX_NAME_LENGTH];
    int time;

    // timer.txt 파일에서 가장 최근에 입력된 홀수 줄의 닉네임과 짝수 줄의 시간 찾기
    while (fgets(name, sizeof(name), file) != NULL) {
        if (fgets(name, sizeof(name), file) != NULL) {
            strncpy(recentName, name, sizeof(recentName)); // 홀수 줄의 닉네임 저장
            fgets(name, sisszeof(name), file); // 짝수 줄로 이동
            sscanf(name, "%d", &recentTime); // 짝수 줄의 시간 저장
        }
    }

    fclose(file);

    // 초를 분 단위로 변환하여 출력
    int minutes = recentTime / 60; // 분 계산
    int seconds = recentTime % 60; // 초 계산

    printf("닉네임: %s", recentName);
    printf("클리어 시간: %d분 %d초\n", minutes, seconds);
}


//순위표 오름차순 정렬 후 1~3위 출력
typedef struct {
    char name[MAX_NAME_LENGTH];
    int time;
} PlayerData;

// 비교 함수
int compare(const void* a, const void* b) {
    const PlayerData* playerA = (const PlayerData*)a;
    const PlayerData* playerB = (const PlayerData*)b;

    return playerA->time - playerB->time;
}

void Ranking_table() {
    FILE* file = fopen("timer.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    PlayerData players[MAX_ENTRIES];
    int numEntries = 0;

    char line[MAX_NAME_LENGTH + 10];
    char name[MAX_NAME_LENGTH];
    int time;

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%s", name);
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d", &time);
            strncpy(players[numEntries].name, name, MAX_NAME_LENGTH);
            players[numEntries].time = time;
            numEntries++;
        }

        if (numEntries >= MAX_ENTRIES) {
            printf("최대 엔트리 수를 초과했습니다.\n");
            break;
        }
    }

    fclose(file);

    qsort(players, numEntries, sizeof(PlayerData), compare);

    int numPrinted = 0;
    for (int i = 0; i < numEntries && numPrinted < 3; i++) {
        int minutes = players[i].time / 60; // 초를 분으로 변환
        int seconds = players[i].time % 60; // 초 단위 계산

        printf("%d위 => 닉네임: %s, 시간: %d분 %d초\n", numPrinted + 1, players[i].name, minutes, seconds);
        numPrinted++;
    }
}
