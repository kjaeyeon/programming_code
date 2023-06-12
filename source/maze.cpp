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

extern int maze[SIZE][SIZE];
extern int distance[SIZE][SIZE];
int stage = 1;
int clear = 0;

void move_enemy(int* enemyX, int* enemyY, int p_x, int p_y);
int calculate_distance(int startX, int startY, int targetX, int targetY);

// 범위 확인
int is_valid(int x, int y) {
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

// 시작 위치에서 DFS 알고리즘을 사용하여 미로 생성
void generate_maze(int x, int y) {
    int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} }; // 이동 방향 (아래, 위, 오른쪽, 왼쪽)
    int order[4] = { 0, 1, 2, 3 }; // 이동 순서를 랜덤화하기 위한 배열

    // 이동 순서를 랜덤하게 섞음
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }

    // 현재 위치를 통로로 설정
    maze[x][y] = 0;

    // 랜덤하게 섞은 이동 순서에 따라 DFS 탐색 진행
    for (int i = 0; i < 4; i++) {
        int dx = dir[order[i]][0];
        int dy = dir[order[i]][1];

        int nx = x + (dx * 2);
        int ny = y + (dy * 2);

        if (is_valid(nx, ny) && maze[nx][ny] == 1) {
            maze[x + dx][y + dy] = 0;
            generate_maze(nx, ny);
        }
    }
}

// 생성된 미로 출력
void print_maze(int destX, int destY, int p_x, int p_y, int enemyX, int enemyY) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 1) {
                pos.X = j * 2;
                pos.Y = i;
                SetConsoleCursorPosition(hConsole, pos);
                setConsoleColor(FOREGROUND_GREEN); //초록색
                printf("■"); // 벽 출력
            }
            else if (i == destX && j == destY) {
                pos.X = j * 2;
                pos.Y = i;
                SetConsoleCursorPosition(hConsole, pos);
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);//노란색
                printf("★"); // 목적지 출력
            }
            else if (i == p_x && j == p_y) {
                pos.X = j * 2;
                pos.Y = i;
                SetConsoleCursorPosition(hConsole, pos);
                printf("●"); // 플레이어 출력
            }
            else if (i == enemyX && j == enemyY) {
                pos.X = j * 2;
                pos.Y = i;
                SetConsoleCursorPosition(hConsole, pos);
                setConsoleColor(FOREGROUND_RED);  // 빨간색
                printf("▼"); // 적 출력
            }
            else {
                pos.X = j * 2;
                pos.Y = i;
                SetConsoleCursorPosition(hConsole, pos);
                printf("  "); // 통로 출력
            }
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 텍스트 색상을 기본값으로 변경
        }
        puts("");
    }
}

// BFS 알고리즘을 사용하여 두 지점 사이의 거리를 계산.
int calculate_distance(int startX, int startY, int targetX, int targetY) {
    int visited[SIZE][SIZE];    // 방문한 셀을 추적하기 위한 배열
    int queue[SIZE * SIZE][2];  // BFS 탐색을 수행하기 위한 큐
    int front = 0, rear = 0;    // 큐의 front와 rear 포인터

    // 방문한 셀과 거리 배열 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            visited[i][j] = 0;        // 모든 셀을 방문하지 않은 상태로 표시.
            distance[i][j] = -1;      // 거리를 -1로 초기화 (도달할 수 없음을 나타냄)
        }
    }

    visited[startX][startY] = 1;    // 시작 셀을 방문한 것으로 표시
    distance[startX][startY] = 0;   // 시작 셀로부터 시작 셀까지의 거리는 0
    queue[rear][0] = startX;        // 시작 셀의 X 좌표를 큐에 삽입
    queue[rear][1] = startY;        // 시작 셀의 Y 좌표를 큐에 삽입
    rear++;                         // rear 포인터를 증가

    while (front < rear) {  // 큐가 비어있지 않은 동안 반복
        int x = queue[front][0];    // 큐에서 현재 셀의 X 좌표를 꺼냄
        int y = queue[front][1];    // 큐에서 현재 셀의 Y 좌표를 꺼냄
        front++;                    // front 포인터를 증가시킵니다.

        if (x == targetX && y == targetY) {
            // 현재 셀이 목표 셀인 경우 거리를 반환
            return distance[x][y];
        }

        // 가능한 방향을 나타내는 배열: 위, 아래, 왼쪽, 오른쪽
        int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        // 현재 셀에서 네 방향을 탐색
        for (int i = 0; i < 4; i++) {
            int dx = dir[i][0];      // X 방향 (행)
            int dy = dir[i][1];      // Y 방향 (열)
            int nx = x + dx;         // 새로운 X 좌표
            int ny = y + dy;         // 새로운 Y 좌표

            // 새로운 좌표가 유효하고 방문하지 않았으며 벽이 아닌지 확인
            if (is_valid(nx, ny) && !visited[nx][ny] && maze[nx][ny] != 1) {
                visited[nx][ny] = 1;                            // 셀을 방문한 것으로 표시
                distance[nx][ny] = distance[x][y] + 1;          // 거리를 업데이트
                queue[rear][0] = nx;                            // 새로운 X 좌표를 큐에 삽입
                queue[rear][1] = ny;                            // 새로운 Y 좌표를 큐에 삽입
                rear++;                                         // rear 포인터를 증가
            }
        }
    }

    // 목표 셀에 도달할 수 없는 경우 -1을 반환
    return -1;
}

void move_enemy(int* enemyX, int* enemyY, int p_x, int p_y) {
    int distance[SIZE][SIZE];  // 두 지점 사이의 거리를 저장할 배열
    int minDistance = SIZE * SIZE;  // 최소 거리를 저장할 변수, 최대값으로 초기화
    int minNeighborX = *enemyX;  // 최소 거리를 갖는 이웃 위치의 X 좌표
    int minNeighborY = *enemyY;  // 최소 거리를 갖는 이웃 위치의 Y 좌표

    int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };  // 상하좌우 이동을 나타내는 방향 배열

    for (int i = 0; i < 4; i++) {  // 상하좌우 각 방향에 대해 반복
        int dx = dir[i][0];  // 현재 방향의 X 좌표 변화량
        int dy = dir[i][1];  // 현재 방향의 Y 좌표 변화량
        int nx = *enemyX + dx;  // 이웃 위치의 X 좌표
        int ny = *enemyY + dy;  // 이웃 위치의 Y 좌표

        if (is_valid(nx, ny) && maze[nx][ny] != 1) {  // 이웃 위치가 유효하고 벽이 아닌 경우
            distance[nx][ny] = calculate_distance(nx, ny, p_x, p_y);  // 이웃 위치와 플레이어 위치 사이의 거리 계산

            if (distance[nx][ny] < minDistance) {  // 현재 이웃 위치와 플레이어 위치 사이의 거리가 최소 거리보다 작은 경우
                minDistance = distance[nx][ny];  // 최소 거리 업데이트
                minNeighborX = nx;  // 최소 거리를 갖는 이웃 위치의 X 좌표 업데이트
                minNeighborY = ny;  // 최소 거리를 갖는 이웃 위치의 Y 좌표 업데이트
            }
        }
    }

    *enemyX = minNeighborX;  // 적 캐릭터의 X 좌표 업데이트
    *enemyY = minNeighborY;  // 적 캐릭터의 Y 좌표 업데이트
}



void maze1_main() {
    srand(time(NULL)); // 난수 생성기 초기화

    int p_x = 1, p_y = 1; // 플레이어의 초기 위치 (1, 1)
    int rand_length;
    int rand_width;

    // 모든 셀을 벽으로 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = 1;
        }
    }

    generate_maze(SIZE - 2, SIZE - 2); // (SIZE - 2, SIZE - 2)에서 미로 생성 시작


    //목적지 위치 설정
    int destX = -1, destY = -1;
    int destX2 = -1, destY2 = -1;
    int dext = calculate_distance(1, 1, SIZE - 2, SIZE - 2);
    int flag = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (dext / 2 == distance[i][j])
            {
                int dext2 = calculate_distance(i, j, SIZE - 2, SIZE - 2) + calculate_distance(1, 1, i, j);
                if (dext == dext2)
                {
                    destX = i;
                    destY = j;
                }
            }
        }
    }

    //길이 하나로 존재하던 미로의 벽에 구멍을 하나 뚫음으로 길을 두개를 만듦
    while (1) {
        rand_length = rand() % (SIZE - 1);
        rand_width = rand() % (SIZE - 1);

        if (rand_length == 0 || rand_width == 0) continue;
        if (maze[rand_length][rand_width] == 1)
        {
            if (maze[rand_length + 1][rand_width] == 1 && maze[rand_length - 1][rand_width] == 1)
            {
                if (maze[rand_length][rand_width - 1] != 1) break;
            }
            else if (maze[rand_length][rand_width - 1] == 1)
            {
                if (maze[rand_length + 1][rand_width] != 1 && maze[rand_length - 1][rand_width] != 1) break;
            }
        }
    }
    maze[rand_length][rand_width] = 0;

    // 적의 위치설정
    int e_x = SIZE - 2;
    int e_y = SIZE - 2;
    int count = 0;
    // 플레이어와 목적지 위치 설정
    maze[p_x][p_y] = 2; // 플레이어
    maze[destX][destY] = 4;//목적지
    maze[e_x][e_y] = 3;//적


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //화면커서 깜빡임 제거
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursor_info);

    while (1) {
        print_maze(destX, destY, p_x, p_y, e_x, e_y);

        char ch = _getch(); // 방향키를 입력받음

        // 방향키 입력에 따른 플레이어 위치변화
        switch (ch) {
        case 72: //위방향키
            if (is_valid(p_x - 1, p_y) && maze[p_x - 1][p_y] != 1) {
                maze[p_x][p_y] = 0;
                p_x--;
                if (count == 2) {
                    move_enemy(&e_x, &e_y, p_x, p_y);
                }// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
                count++;
                if (count == 3)count = 0;
            }
            break;
        case 80: //아래방향키
            if (is_valid(p_x + 1, p_y) && maze[p_x + 1][p_y] != 1) {
                maze[p_x][p_y] = 0;
                p_x++;
                if (count == 2) {
                    move_enemy(&e_x, &e_y, p_x, p_y);
                }// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
                count++;
                if (count == 3)count = 0;
            }
            break;
        case 75: //왼쪽방향키
            if (is_valid(p_x, p_y - 1) && maze[p_x][p_y - 1] != 1) {
                maze[p_x][p_y] = 0;
                p_y--;
                if (count == 2) {
                    move_enemy(&e_x, &e_y, p_x, p_y);
                }// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
                count++;
                if (count == 3)count = 0;
            }
            break;
        case 77: //오른쪽방향키
            if (is_valid(p_x, p_y + 1) && maze[p_x][p_y + 1] != 1) {
                maze[p_x][p_y] = 0;
                p_y++;
                if (count == 2) {
                    move_enemy(&e_x, &e_y, p_x, p_y);
                }// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
                count++;
                if (count == 3)count = 0;
            }
            break;
        default:
            break;
        }


        if (p_x == destX && p_y == destY) {
            system("cls");
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
            printf("\t\t축하합니다!!! 1스테이지 클리어!!\n");
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 텍스트 색상을 기본값으로 변경
            clear++;
            break;
        }

        if (p_x == e_x && p_y == e_y) {
            system("cls");
            PlaySound(TEXT("C:\\Users\\jsn30\\OneDrive\\바탕 화면\\3조 미로찾기\\CNJ_MAZE\\CNJ_MAZE\\scr.wav"), NULL, SND_FILENAME | SND_ASYNC);
            setConsoleColor(FOREGROUND_RED);  // 텍스트 색상을 빨간색으로 변경
            system("cls");
            image_add();
            system("cls");
            printf("\t\t당신은 귀신에게 붙잡혔습니다.\n");
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 텍스트 색상을 기본값으로 변경
            break;
        }

    }
}

void maze2_main() {
    srand(time(NULL)); // 난수 생성기 초기화

    int p_x = 1, p_y = 1; // 플레이어의 초기 위치 (1, 1)
    int rand_length;
    int rand_width;

    // 모든 셀을 벽으로 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = 1;
        }
    }

    generate_maze(SIZE - 2, SIZE - 2); // 우측아래에서 미로 생성 시작

    //목적지 위치 설정
    int destX = -1, destY = -1;
    int destX2 = -1, destY2 = -1;
    int dext = calculate_distance(1, 1, SIZE - 2, SIZE - 2);
    int flag = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (dext / 2 == distance[i][j])
            {
                int dext2 = calculate_distance(i, j, SIZE - 2, SIZE - 2) + calculate_distance(1, 1, i, j);
                if (dext == dext2)
                {
                    destX = i;
                    destY = j;
                }
            }
        }
    }

    while (1) {
        rand_length = rand() % (SIZE - 1);
        rand_width = rand() % (SIZE - 1);

        if (rand_length == 0 || rand_width == 0) continue;
        if (maze[rand_length][rand_width] == 1)
        {
            if (maze[rand_length + 1][rand_width] == 1 && maze[rand_length - 1][rand_width] == 1)
            {
                if (maze[rand_length][rand_width - 1] != 1) break;
            }
            else if (maze[rand_length][rand_width - 1] == 1)
            {
                if (maze[rand_length + 1][rand_width] != 1 && maze[rand_length - 1][rand_width] != 1) break;
            }
        }
    }
    maze[rand_length][rand_width] = 0;

    // 적의 위치설정
    int e_x = SIZE - 2;
    int e_y = SIZE - 2;
    int count = 0;
    // 플레이어와 목적지 위치 설정
    maze[p_x][p_y] = 2; // 플레이어
    maze[destX][destY] = 4;//목적지
    maze[e_x][e_y] = 3;//적


    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //화면커서 깜빡임 제거
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 100;
    cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursor_info);

    while (1) {
        print_maze(destX, destY, p_x, p_y, e_x, e_y);

        char ch = _getch(); // 방향키를 입력받음

        // 방향키 입력에 따른 플레이어 위치변화
        switch (ch) {
        case 72: //위방향키
            if (is_valid(p_x - 1, p_y) && maze[p_x - 1][p_y] != 1) {
                maze[p_x][p_y] = 0;
                p_x--;
                move_enemy(&e_x, &e_y, p_x, p_y);// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
            }
            break;
        case 80: //아래방향키
            if (is_valid(p_x + 1, p_y) && maze[p_x + 1][p_y] != 1) {
                maze[p_x][p_y] = 0;
                p_x++;
                move_enemy(&e_x, &e_y, p_x, p_y);// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
            }
            break;
        case 75: //왼쪽방향키
            if (is_valid(p_x, p_y - 1) && maze[p_x][p_y - 1] != 1) {
                maze[p_x][p_y] = 0;
                p_y--;
                move_enemy(&e_x, &e_y, p_x, p_y);// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
            }
            break;
        case 77: //오른쪽방향키
            if (is_valid(p_x, p_y + 1) && maze[p_x][p_y + 1] != 1) {
                maze[p_x][p_y] = 0;
                p_y++;
                move_enemy(&e_x, &e_y, p_x, p_y);// 적이 플레이어에게 이동
                maze[p_x][p_y] = 2;
            }
            break;
        default:
            break;
        }

        if (p_x == destX && p_y == destY) {
            system("cls");
            clear++;
            break;
        }

        if (p_x == e_x && p_y == e_y) {
            system("cls");
            PlaySound(TEXT("C:\\Users\\jsn30\\OneDrive\\바탕 화면\\3조 미로찾기\\CNJ_MAZE\\CNJ_MAZE\\scr.wav"), NULL, SND_FILENAME | SND_ASYNC);
            setConsoleColor(FOREGROUND_RED);  // 텍스트 색상을 빨간색으로 변경
            system("cls");
            image_add();
            system("cls");
            printf("\t\t당신은 귀신에게 붙잡혔습니다.\n");
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 텍스트 색상을 기본값으로 변경
            break;
        }
    }
}
