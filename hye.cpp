#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define Max_id_size 20
clock_t start, end;  // 전역 변수로 선언

double game_timer(int stage, clock_t start ,clock_t end) {

    switch(stage){
        case 1:
        static double stage1_time = 0, stage2_time = 0; //정적 변수를 사용하여 각 값들이 저장되어 있도록 저장
        stage1_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        break;

        default :
        stage2_time = ((double) (end - start)) / CLOCKS_PER_SEC;
        //(총 시간)
        double total_time = stage1_time + stage2_time;

        // 사용자 아이디 입력 받기
        char user_id[20];
        printf("사용자 아이디를 입력하세요: ");
        scanf("%s", user_id);

        // 파일에 총 시간 저장
        FILE* file = fopen("timer.txt", "a"); //덧붙히기 모드로 열기
        if (file != NULL) {
            fprintf(file, "[%s] Total Time: %.2f초\n",user_id, total_time);
            fclose(file);
            return total_time;
        }
        else {
            printf("파일을 열 수 없습니다.\n");
        }
        printf("아무 키나 누르세요...\n");
        getch();

    }

}

