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
void game_story(int );
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
bool clear(int stage);
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
void main_maze();

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

//게임 메뉴
int game_menu() {
    int stage = 1; //메뉴를 불러올때마다 1스테이지부터 시작
    char choice;
    while (1) {
        printf("============================================\n");
        printf("▄▄▄█████▓ ██▀███   ██▓ ▄████▄   ██ ▄█▀    ▒█████   ██▀███      ███▄ ▄███▓ █    ██ ▓█████▄ ▓█████  ██▀███   ▐██▌\n");    
        printf("▓  ██▒ ▓▒▓██ ▒ ██▒▓██▒▒██▀ ▀█   ██▄█▒    ▒██▒  ██▒▓██ ▒ ██▒   ▓██▒▀█▀ ██▒ ██  ▓██▒▒██▀ ██▌▓█   ▀ ▓██ ▒ ██▒ ▐██▌    \n");
        printf("▒ ▓██░ ▒░▓██ ░▄█ ▒▒██▒▒▓█    ▄ ▓███▄░    ▒██░  ██▒▓██ ░▄█ ▒   ▓██    ▓██░▓██  ▒██░░██   █▌▒███   ▓██ ░▄█ ▒ ▐██▌    \n");
        printf("░ ▓██▓ ░ ▒██▀▀█▄  ░██░▒▓▓▄ ▄██▒▓██ █▄    ▒██   ██░▒██▀▀█▄     ▒██    ▒██ ▓▓█  ░██░░▓█▄   ▌▒▓█  ▄ ▒██▀▀█▄   ▓██▒    \n");
        printf("  ▒██▒ ░ ░██▓ ▒██▒░██░▒ ▓███▀ ░▒██▒ █▄   ░ ████▓▒░░██▓ ▒██▒   ▒██▒   ░██▒▒▒█████▓ ░▒████▓ ░▒████▒░██▓ ▒██▒ ▒▄▄    \n"); 
        printf("  ▒ ░░   ░ ▒▓ ░▒▓░░▓  ░ ░▒ ▒  ░▒ ▒▒ ▓▒   ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░   ░ ▒░   ░  ░░▒▓▒ ▒ ▒  ▒▒▓  ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░ ░▀▀▒    \n");
        printf("    ░      ░▒ ░ ▒░ ▒ ░  ░  ▒   ░ ░▒ ▒░     ░ ▒ ▒░   ░▒ ░ ▒░   ░  ░      ░░░▒░ ░ ░  ░ ▒  ▒  ░ ░  ░  ░▒ ░ ▒░ ░  ░   \n"); 
        printf("  ░        ░░   ░  ▒ ░░        ░ ░░ ░    ░ ░ ░ ▒    ░░   ░    ░      ░    ░░░ ░ ░  ░ ░  ░    ░     ░░   ░     ░   \n"); 
        printf("            ░      ░  ░ ░      ░  ░          ░ ░     ░               ░      ░        ░       ░  ░   ░      ░      \n"); 
        printf("                      ░                                                            ░                               \n\n\n");


        printf("███████ ████████  █████  ██████  ████████      ██ ██████  ██    ██ ███████ ██   ██     ███████ ██              \n");                                 
        printf("██         ██    ██   ██ ██   ██    ██        ██  ██   ██ ██    ██ ██      ██   ██     ██       ██ \n");                                             
        printf("███████    ██    ███████ ██████     ██        ██  ██████  ██    ██ ███████ ███████     ███████  ██ \n");                                             
        printf("     ██    ██    ██   ██ ██   ██    ██        ██  ██      ██    ██      ██ ██   ██          ██  ██  \n");                                            
        printf("███████    ██    ██   ██ ██   ██    ██         ██ ██       ██████  ███████ ██   ██     ███████ ██  \n");                                             
        printf("                                                                                                  \n\n\n");                                              
                                                                                                                                                        
        printf("██████  ██    ██ ██      ███████      ██ ██████  ██    ██ ███████ ██   ██     ██████  ██   \n");                                                     
        printf("██   ██ ██    ██ ██      ██          ██  ██   ██ ██    ██ ██      ██   ██     ██   ██  ██  \n");                                                     
        printf("██████  ██    ██ ██      █████       ██  ██████  ██    ██ ███████ ███████     ██████   ██  \n");                                                     
        printf("██   ██ ██    ██ ██      ██          ██  ██      ██    ██      ██ ██   ██     ██   ██  ██  \n");                                                     
        printf("██   ██  ██████  ███████ ███████      ██ ██       ██████  ███████ ██   ██     ██   ██ ██    \n");                                                    
        printf("                                                                                          \n\n\n");                                                      
                                                                                                                                                        
        printf("███████ ██   ██ ██ ████████      ██ ██████  ██    ██ ███████ ██   ██     ███████ ██ \n");                                                            
        printf("██       ██ ██  ██    ██        ██  ██   ██ ██    ██ ██      ██   ██     ██       ██  \n");                                                          
        printf("█████     ███   ██    ██        ██  ██████  ██    ██ ███████ ███████     █████    ██  \n");                                                          
        printf("██       ██ ██  ██    ██        ██  ██      ██    ██      ██ ██   ██     ██       ██      \n");                                                      
        printf("███████ ██   ██ ██    ██         ██ ██       ██████  ███████ ██   ██     ███████ ██  \n\n\n");

        printf("*원하시는 게임 선택지를 입력해주세요 : _\b");
        scanf("%c", &choice); //사용자 입력받기
        if (choice == 's' || choice == 'S')//s를 입력한다면
            return 0; //메뉴나가기}
        else if (choice == 'r' || choice == 'R') //r을 입력한다면
            game_rule(); //rule 불러오기
        else if (choice == 'e' || choice == 'E') //e를 입력한다면
            exit(1); //나가기
        else printf("잘못된 문자를 입력하셨습니다.");
        system("cls");
    }
}

//게임 시작 화면
void game_start(int stage) {
    switch (stage) //입력받은 스테이지가 2라면 전부 실행, 1이면 defalut값만 실행
        case 2: gold_item();
defalut:
    main_maze();
    start = clock(); //함수 위치가 다른곳인데도 실행이 되는지 확인
    playing = 1;
}

//공포 이미지 추가
void image_add() {
    system("cls"); //

    FILE* file;
    char ch;

    // 그림을 저장한 텍스트 파일을 연다
    file = fopen("horror.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }

    // 파일 내용을 한 줄씩 읽어서 출력
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
    Sleep(5000); // 그림을 보여줌

    system("cls"); // 터미널을 청소
}


//게임 설명 화면
void game_rule() {
    printf("고스트는 당신에게 제일 빠른길로 다가오고 있습니다.\n최대한 빨리 목적지를 향해 도망가세요!\n (황금열쇠)는 2스테이지에서 당신을 나가게 도와줄 것 입니다!");
}

//게임 스토리
void game_story(int stage)
{
    switch(stage){
        case 1:
        printf("...\n");
        Sleep(2000);
        printf("(바닥에 떨어진 전단지를 발견한다)\n");
        Sleep(1000);
        printf("[할로윈 기념 파티에 당신을 초대합니다!]\n");
        printf("[진정한 귀신들만이 올 수 있는 특별한 파티]\n");
        printf("[한껏 꾸미고 아름다운 모습을 기대하겠습니다]\n");
        printf("[위치: @@시@@동 @@#$ 저택 지하 1층]\n");
        Sleep(1000);
        printf("(흥미가 생긴 주인공은 가기로 결정한다.)\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("귀신분장을 하고 도착한 주인공은 대저택 정문 앞에서\n ");
        printf("마찬가지로 귀신 분장을 한 사람에게 안내를 받아 파티장에 도착하였다.\n");
        Sleep(1000);
        printf("생각보다 많은 인원에 놀란 한편 주인공은 이상한 점을 발견한다.\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("기괴할 정도로 조용하고 스산한 분위기\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("그리고 흐린 발끝\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("주인공은 상황을 인지하지 못하다가 한 호박 귀신이 쫓아오는 것을 발견하곤 곧바로 자신이 왔던 문으로 뛰어간다.\n");
        break;
        case 2:
        printf("미로에서 도망치다 보니 계단이 보인다.\n");
        printf("지상으로 올라가는 길\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("주인공은 힘차게 올라갔지만 다시 보이는 미로에 암담하다...\n");
        Sleep(1000);
        printf("2 Stage Start\n");
        printf("(열쇠를 찾아야 탈출구로 나갈 수 있습니다!)\n");
        printf("계속하려면 아무키나 누르세요...");
        getch();
        break;
        case 3:
        printf("열쇠로 급히 문을 열고 드디어 밖으로 나온 주인공\n");
        Sleep(1000);
        printf("밖은 이미 어두워졌고 문 옆엔 아까 자신을 안내해준 귀신을 발견하였다.\n");
        Sleep(1000);
        printf("무표정한 얼굴로 다가오는 그들을 따돌리며 황급히 자신의 집으로 도망간다.\n");
        Sleep(1000);
        printf("다행히 어느 순간부터 그들은 따라오지 않고 노려보기만 하였고,\n");
        Sleep(1000);
        printf("나중에 경찰에 신고하고 찾아간 그곳에는 아무것도 찾을 수 없었다...\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("...\n");
        Sleep(1000);
        printf("!축하합니다!\n");
        printf("모든 스테이지를 클리어하셨습니다!\n");
    }
	}

//게임 종료 조건
bool clear(int stage, int playing) {
    playing = 0;
    switch (stage) {
    case 1:
        if (p_x == g_x && p_y == g_y) { //팩맨과 고스트의 위치가 같아진다면
            printf("탈출 실패"); //화면을 지우고 가운데 출력되도록
            game_menu();
        }
        else if (p_x == d_x && p_y == d_y) //팩맨과 목적지의 위치가 같다면
            return 1;
        break;
    case 2:
        if (p_x == g_x && p_y == g_y) { //팩맨과 고스트의 위치가 같다면
            printf("탈출 실패"); //화면을 지우고 가운데에 출력되도록
            game_menu();
        }
        else if (p_x == d_x && p_y == d_y)
            if (key_inven == 1) //열쇠를 가지고 있는 변수를 만들어서 가지면 1, 없으면 0
                return 1;
            else
                showAndHideText("열쇠를 가지고 와야 나갈 수 있다.");
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
                // else if (maze_str[i][j] == WALL) { //벽이랑 만났을때를 어떻게 해야할 지 모르겠음
                //     printf("■"); //벽
                }
                else { // 길은 공백으로 표시
                    printf(" ");
                }
            }
        }
        printf("\n"); // 한 줄 출력 후 개행
    }

void showAndHideText(char* text) { //보여주고 사라지는 텍스트
    gotoxy(t_x, t_y);
    setConsoleColor(12); //색깔을 빨간색으로 설정
    printf("%s", text);  // 텍스트를 출력합니다.
    Sleep(5000);
    int i;
    for (i = 0; i < 30; i++) {
        printf("\b");
    }
    for (i = 0; i < 30; i++) {
        printf(" ");
    }
    for (i = 0; i < 30; i++) {
        printf("\b");
    }
    setConsoleColor(15);
}
void gotoxy(int x, int y) { //텍스트 출력 위치를 바꾸는 함수
    COORD Pos = { x - 1, y - 1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setConsoleColor(int colorCode) { //글씨의 색깔을 바꾸는 함수
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

// 주어진 좌표의 셀이 벽인지 아닌지 확인 (블록체크)
int is_block(int x, int y) {
    return maze[x][y] == 1;
}