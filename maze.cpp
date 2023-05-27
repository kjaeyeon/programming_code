#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 25 // 미로의 크기

int maze[SIZE][SIZE];

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
void print_maze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 1) {
                printf("■"); // 벽 출력
            }
            else {
                printf("  "); // 통로 출력
            }
        }
        printf("\n");
    }
}

int main_maze() {
    srand(time(NULL)); // 난수 생성기 초기화

    // 모든 셀을 벽으로 초기화
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = 1;
        }
    }

    generate_maze(1, 1); // (1, 1)에서 미로 생성 시작
    print_maze(); // 생성된 미로 출력

    return 0;
}
