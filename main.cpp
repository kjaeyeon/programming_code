
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

// 오름차순 정렬을 위한 비교 함수
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void sortStageClearTime() {
    int* stage_clear_time = NULL; // 스테이지 클리어 시간이 들어있는 배열
    int size = 0;
    int i;

    // 파일 열기
    FILE* file = fopen("stage_clear_time.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 파일에서 데이터 읽기
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        size++;
        int* temp = (int*)realloc(stage_clear_time, size * sizeof(int));
        if (temp == NULL) {
            printf("메모리 할당 오류가 발생했습니다.\n");
            fclose(file);
            free(stage_clear_time);
            return;
        }
        stage_clear_time = temp;
        stage_clear_time[size - 1] = num;
    }

    // 파일 닫기
    fclose(file);

    if (size == 0) {
        printf("데이터가 없습니다.\n");
        free(stage_clear_time);
        return;
    }

    // 배열 정렬
    qsort(stage_clear_time, size, sizeof(int), compare);

    //배열 상위 3개 출력하기
    printf("순위\n");
    for (int i = 0; i < 3; i++) {
        printf("%d\n", stage_clear_time[i]);
    }

    free(stage_clear_time);
}