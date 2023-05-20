#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

int main() {
    PlaySound(TEXT("C:\\maze.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // 게임 실행

    PlaySound(NULL, NULL, SND_ASYNC);

    return 0;
}