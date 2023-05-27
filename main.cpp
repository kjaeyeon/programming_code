
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
            sortStageClearTime(); //오름차순으로 시간 정렬
            Ranking_table();
            if (나가기를 누른다면){
                system("cls");
                game_menu();
            }
        }
    }
return 0;
}
//게임 설명 화면
void game_rule() {
    printf("고스트는 당신에게 제일 빠른길로 다가오고 있습니다.\n최대한 빨리 목적지를 향해 도망가세요!\n (황금열쇠)는 2스테이지에서 당신을 나가게 도와줄 것 입니다!");
}
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
    printf("총 시간: %.2f초\n", total_time);

    // 사용자 아이디 입력 받기
    char user_id[20];
    printf("사용자 아이디를 입력하세요: ");
    scanf_s("%s", &user_id);

    // 파일에 총 시간 저장
    FILE* fp = fopen("timer.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "Total Time: %.2f초\n", total_time);
        fclose(fp);
    }
    else {
        printf("파일을 열 수 없습니다.\n");
    }

    // total_time을 보여주기 위해 사용자 입력 대기
    printf("아무 키나 누르세요...\n");
    while (getchar() != '\n') {}  // Enter 키까지 입력 대기
}

//게임 종료 조건
bool clear(int stage,int playing) {
    playing = 0;
    switch (stage) {
    case 1:
        if (p_x==g_x && p_y==g_y) { //팩맨과 고스트의 위치가 같아진다면
            printf("탈출 실패");
            game_menu();
        }
        else if (p_x == d_x && p_y == d_y) //팩맨과 목적지의 위치가 같다면
            return 1;
        break;
    case 2:
        if (p_x == g_x && p_y == g_y) { //팩맨과 고스트의 위치가 같다면
            printf("탈출 실패");
            game_menu();
        }
        else if (p_x == d_x && p_y == d_y)
            if (key_inven==1 ) //열쇠를 가지고 있는 변수를 만들어서 가지면 1, 없으면 0
                return 1;
            else
                printf("열쇠를 가지고 와야 나갈 수 있다.");
        return 0;
    }
}
//시야 제한 ->코딩 후 문제점이 발생하면 그래픽 함수 사용
void display(int x, int y) {
    for (int i = x - 2; i <= x + 2; i++) {
        for (int j = y - 2; j <= y + 2; j++) {
            if (i >= 0 && i < ROW && j >= 0 && j < COL) { // 미로 범위 내에서만 출력
                if (i == x && j == y) {
                    printf("@"); //현재 위치 임의
                }
                else if (maze_str[i][j] == WALL) { //벽이랑 만났을때를 어떻게 해야할 지 모르겠음
                    printf("■"); //벽
                }
                else { // 길은 공백으로 표시
                    printf(" ");
                }
            }
        }
        printf("\n"); // 한 줄 출력 후 개행
    }
}
void gotoxy(int x, int y) {
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//오름차순 정렬 후 1~3위 출력
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
