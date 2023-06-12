#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include"all_about.h"



extern int stage;
extern int clear;

void game_rule();
void text_color(int foreground, int backgrond);

int game_menu() {
    char choice;
    char back;
    while (1) {
        system("cls");
        text_color(LIGHTRED, BLACK);  // 텍스트 색상을 청색으로 변경
        printf(" ______  ____   ____     __  __  _       ___   ____       ___ ___  __ __  ____   ___      ___  ____ \n");
        printf("|      T|    \\ l    j   /  ]|  l/ ]     /   \\ |    \\     |   T   T|  T  T|    \\ |   \\    /  _]|    \\\n");
        printf("|      ||  D  ) |  T   /  / |  ' /     Y     Y|  D  )    | _   _ ||  |  ||  D  )|    \\  /  [_ |  D  )\n");
        printf("l_j  l_j|    /  |  |  /  /  |    \\     |  O  ||    /     |  \\_/  ||  |  ||    / |  D  YY    _]|    / \n");
        printf("  |  |  |    \\  |  | /   \\_ |     Y    |     ||    \\     |   |   ||  :  ||    \\ |     ||   [_ |    \\ \n");
        printf("  |  |  |  .  Y j  l \\     ||  .  |    l     !|  .  Y    |   |   |l     ||  .  Y|     ||     T|  .  Y\n");
        printf("  l__j  l__j\\_j|____j \\____jl__j\\_j     \\___/ l__j\\_j    l___j___j \\__,_jl__j\\_jl_____jl_____jl__j\\_j\n");
        text_color(YELLOW, BLACK);
        gotoxy(20, 12);
        printf("게임스타트(S입력)\n");
        gotoxy(20, 14);
        printf("게임설명(R입력)\n");
        gotoxy(20, 16);
        printf("게임나가기(E입력)\n");
        text_color(WHITE, BLACK);
        choice = getch(); //사용자 입력받기

        if (choice == 's' || choice == 'S') {//s를 입력한다면
            system("cls");
            return 0; //메뉴나가기}
        }
        else if (choice == 'r' || choice == 'R') {//r을 입력한다면
            game_rule(); //rule 불러오기
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
            printf("\n\n아무키나 눌러 돌아가기...\n");
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            back = getch();
        }
        else if (choice == 'e' || choice == 'E') { //e를 입력한다면
            exit(1); //나가기
        }
    }
}
//공포 이미지 추가
void image_add()
{
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
    Sleep(3500); // 그림을 보여줌

    system("cls"); // 터미널을 청소
}
void image_add2() //계단그림
{
    system("cls"); //

    FILE* file;
    char ch;

    // 그림을 저장한 텍스트 파일을 연다
    file = fopen("stairs.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }

    // 파일 내용을 한 줄씩 읽어서 출력
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
    Sleep(3000); // 그림을 보여줌

    system("cls"); // 터미널을 청소
}
void image_add3() //문 그림
{
    system("cls"); //

    FILE* file;
    char ch;

    // 그림을 저장한 텍스트 파일을 연다
    file = fopen("2_maze_in.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }

    // 파일 내용을 한 줄씩 읽어서 출력
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
    Sleep(2500); // 그림을 보여줌

    system("cls"); // 터미널을 청소
}
void image_add4() //밖으로 탈출
{
    system("cls"); //

    FILE* file;
    char ch;

    // 그림을 저장한 텍스트 파일을 연다
    file = fopen("outside.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.");
        return;
    }

    // 파일 내용을 한 줄씩 읽어서 출력
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);
    Sleep(3000); // 그림을 보여줌

    system("cls"); // 터미널을 청소
}

//게임 설명 화면
void game_rule() {
    system("cls");
    printf("당신은 ");
    setConsoleColor(FOREGROUND_BLUE);
    printf("팩맨(●)");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("입니다.\n\n할로윈 파티에 놀러간 당신은 이곳이 ");
    setConsoleColor(FOREGROUND_RED);
    printf("귀신");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("들의 파티임을 깨닫고 ");
    setConsoleColor(FOREGROUND_GREEN);
    printf("미로같은 저택");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("에서 탈출하려 하는데...\n\n부디 ");
    setConsoleColor(FOREGROUND_RED);
    printf("고스트(▼)");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("에게서 도망가 ");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
    printf("목적지(★)");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("에 무사히 도착하세요. \n\n");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
    printf("방향키(→←↑↓)");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("로 조종하여 캐릭터를 움직일 수 있습니다.\n\n");
    setConsoleColor(FOREGROUND_RED);
    printf("고스트(▼)");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("는 가장 빠른 길로 당신에게 다가오고 있으며, 잡히면 게임은 즉시 ");
    setConsoleColor(FOREGROUND_RED);
    printf("종료");
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("하게 됩니다.\n");
}

//게임 스토리
void game_story(int stage, int clear)
{
    char enter;
    if (stage == 1) {
        printf("\t\t...\n");
        Sleep(1500);
        printf("\t\t(바닥에 떨어진 전단지를 발견한다)\n\n");
        Sleep(1500);
        printf("\t\t[할로윈 기념 파티에 당신을 초대합니다!]\n");
        printf("\t\t[진정한 귀신들만이 올 수 있는 특별한 파티]\n");
        printf("\t\t[한껏 꾸미고 아름다운 모습을 기대하겠습니다]\n");
        printf("\t\t[위치: @@시@@동 @@#$ 저택 지하 1층]\n");
        Sleep(1500);
        printf("\t\t(흥미가 생긴 주인공은 가기로 결정한다.)\n\n");
        Sleep(1500);
        printf("\t\t...\n");
        printf("\t\t...\n");
        printf("\t\t...\n");
        Sleep(2000);
        system("cls");
        printf("\n");
        printf("\t\t귀신분장을 하고 도착한 주인공은 대저택 정문 앞에서\n\n");
        Sleep(1500);
        printf("\t\t마찬가지로 귀신 분장을 한 사람에게 안내를 받아 파티장에 도착하였다.\n\n");
        Sleep(1500);
        printf("\t\t생각보다 많은 인원에 놀란 한편 주인공은 이상한 점을 발견한다.\n\n");
        Sleep(1500);
        printf("\t\t...\n\n");
        Sleep(1500);
        printf("\t\t기괴할 정도로 조용하고 스산한 분위기\n\n");
        Sleep(1500);
        printf("\t\t...\n\n");
        Sleep(1500);
        printf("\t\t그리고 흐린 발끝\n\n");
        Sleep(1500);
        printf("\t\t...\n\n");
        Sleep(1500);
        printf("\t\t주인공은 상황을 인지하지 못하다가 한 호박 귀신이 쫓아오는 것을 발견하곤 \n\n");
        Sleep(1500);
        printf("\t\t곧바로 자신이 왔던 문으로 뛰어간다.\n\n");
        Sleep(1500);
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
        printf("\t\t아무버튼이나 눌러 진행하세요...");
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        enter = getch();
        system("cls");
    }
    if (stage == 2) {
        printf("\t\t미로에서 도망치다 보니 계단이 보인다.\n\n");
        Sleep(1500);
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
        image_add2();
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n");
        printf("\t\t지상으로 올라가는 길\n\n");
        Sleep(1500);
        printf("\t\t.");
        Sleep(1500);
        printf(".");
        Sleep(1500);
        printf(".\n\n");
        Sleep(1500);
        printf("\t\t주인공은 힘차게 올라갔지만 다시 보이는 미로에 암담하다...\n\n");
        Sleep(1500);
        image_add3();
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
        printf("\t\t     2 Stage Start!\n\n");
        printf("\t\t마지막 탈출구를 찾으세요!\n\n");
        setConsoleColor(FOREGROUND_GREEN); //노란색
        printf("\t\t아무키나 눌러 계속하세요...");
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        enter = getch();
        system("cls");
    }
    if (clear == 2) {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        image_add4();
        printf("\n");
        printf("\t\t급하게 문이 보이는 곳으로 뛰어가서 힘차게 여니\n\n");
        Sleep(1000);
        printf("\t\t밖은 이미 어두워졌고 문 옆엔 아까 자신을 안내해준 귀신이 멍하니 서있다.\n\n");
        Sleep(1000);
        printf("\t\t아깐 왜 몰랐을까 하고 소름이 끼친다..\n\n");
        Sleep(1000);
        printf("\t\t나는 그 자리를 재빠르게 벗어났고..\n\n");
        Sleep(1000);
        printf("\t\t나중에 경찰과 함께 찾아간 그곳에는 아무것도 찾을 수 없었다...\n");
        Sleep(1000);
        printf("\t\t...\n");
        Sleep(1000);
        printf("\t\t...\n\n");
        Sleep(1000);
        system("cls");
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN); //노란색
        printf("__      ___   ___   __  __   ___  ____   ___  ______ __ __ __     ___  ______ __   ___   __  __  __     __\n");
        Sleep(500);
        printf("||     //    // \\\\  ||\\ ||  // \\\\ || \\\\ // \\\\ | || | || || ||    // \\\\ | || | ||  // \\\\  ||\\ || (( \\    ||\n");
        Sleep(500);
        printf("||    ((    ((   )) ||\\\\|| (( ___ ||_// ||=||   ||   || || ||    ||=||   ||   || ((   )) ||\\\\||  \\\\     ||\n");
        Sleep(500);
        printf("..     \\\\__  \\\\_//  || \\||  \\\\_|| || \\\\ || ||   ||   \\\\_// ||__| || ||   ||   ||  \\\\_//  || \\|| \\_))    ..\n");
        Sleep(1000);
        printf("\n\t\t축하합니다!!! 저택을 탈출하셨습니다!!\n");
        Sleep(1000);
        printf("\t\t아무키나 눌러 계속하세요...\n\n");
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // 텍스트 색상을 기본값으로 변경
        getch();
    }

}

void setConsoleColor(int colorCode) { //글씨의 색깔을 바꾸는 함수
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
// 마우스 좌표 이동
void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void SetConsoleView() {

    system("mode con:cols=110 lines=45");
    system("title TRICK OR MURDER");
}
void text_color(int foreground, int backgrond) {
    int color = foreground + backgrond * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
