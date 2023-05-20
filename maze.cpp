#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 32 //미로크기
int maze_str[SIZE][SIZE];

void creat_maze(int maze_str[SIZE][SIZE]) {
    
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
				maze_str[i][j] = 1;
			}
			else if (i % 2 == 0 && j % 2 == 1) {
				maze_str[i][j] = 1;
			}
			else if (i % 2 == 1 && j % 2 == 0) {
				maze_str[i][j] = 1;
			}
			else {
				maze_str[i][j] = 0;
        }
    }
    //시작점
    int startX = rand() % SIZE;
    int startY = rand() % SIZE;
    maze_str[startX][startY] = 0;

    // Generate the maze paths using a random walk algorithm
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; // Up, Down, Left, Right

    int currentX = startX;
    int currentY = startY;
    while (1) {
        int direction = rand() % 4;
        int nextX = currentX + directions[direction][0];
        int nextY = currentY + directions[direction][1];

        if (nextX >= 0 && nextX < SIZE && nextY >= 0 && nextY < SIZE && maze_str[nextX][nextY] == 1) {
            maze_str[nextX][nextY] = 0;
            maze_str[currentX + directions[direction][0] / 2][currentY + directions[direction][1] / 2] = 0;
            currentX = nextX;
            currentY = nextY;
        }

        int isMazeComplete = 1;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (maze_str[i][j] == 1) {
                    isMazeComplete = 0;
                    break;
                }
            }
        }
        if (isMazeComplete) {
            break;
        }
    }
}

void print_maze(int maze[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 1) {
                printf("█"); // Print wall
            }
            else {
                printf(" "); // Print path
            }
        }
        printf("\n");
    }
}

void maze() {
    srand((unsigned int)time(NULL));//미로값 초기화
    //미로크기 설정
    int length=SIZE, width=SIZE;//길이와 폭 설정
    system("cls");//화면초기화
    creat_maze(maze_str);//미로만들기
    print_maze(maze_str);//미로 출력하기
}
