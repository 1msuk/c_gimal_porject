```c
#include <stdio.h>
#include <stdlib.h>

#define SIZE 15      // 오목판 크기 (15x15)
#define DRAW_BLACK printf("  ○")  // 흑돌 출력
#define DRAW_WHITE printf("  ●")  // 백돌 출력

// 오목판을 출력하는 함수
void Board(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%3d", i);  // 열 번호 출력
    }
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%3d", i);  // 행 번호 출력
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'O') {
                DRAW_BLACK;  // 흑돌 출력
            }
            else if (board[i][j] == 'X') {
                DRAW_WHITE;  // 백돌 출력
            }
            else {
                printf("  .");  // 빈 칸 출력
            }
        }
        printf("\n");
    }
}

// 승리 조건을 검사하는 함수
int win(char board[SIZE][SIZE], int x, int y) {
    char player = board[x][y];  // 현재 플레이어의 돌
    int dire[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };  // 검사할 네 가지 방향

    for (int d = 0; d < 4; d++) {
        int count = 1;  // 현재 돌 포함 카운트
        // 한쪽 방향 검사
        for (int i = 1; i < 5; i++) {
            int nx = x + i * dire[d][0];
            int ny = y + i * dire[d][1];
            if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
                count++;
            }
            else {
                break;
            }
        }
        // 반대쪽 방향 검사
        for (int i = 1; i < 5; i++) {
            int n1 = x - i * dire[d][0];
            int n2 = y - i * dire[d][1];
            if (n1 >= 0 && n1 < SIZE && n2 >= 0 && n2 < SIZE && board[n1][n2] == player) {
                count++;
            }
            else {
                break;
            }
        }
        if (count >= 5) {  // 5개 이상 연속되면 승리
            return 1;
        }
    }
    return 0;  // 승리 조건 미달성
}

int main() {
    char fan[SIZE][SIZE];  // 오목판
    int player;  // 현재 플레이어 (0=흑, 1=백)
    int restart;  // 게임 재시작 여부 변수

    do {
        // 오목판 초기화
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fan[i][j] = '.';
            }
        }

        player = 0;  // 항상 흑돌부터 시작

        while (1) {
            // 현재 오목판 상태를 출력
            Board(fan);
            printf(" %d의 차례입니다. 좌표를 입력하세요 (x, y): ", player + 1);
            int x, y;

            // 플레이어 입력 받기
            scanf("%d %d", &x, &y);

            // 잘못된 입력 처리
            if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || fan[x][y] != '.') {
                printf("잘못된 입력입니다. 다시 입력하세요.\n");
                continue;
            }

            // 돌 배치
            fan[x][y] = (player == 0) ? 'O' : 'X';  // (O: 흑, X: 백)

            // 승리 조건 검사
            if (win(fan, x, y)) {
                Board(fan);
                printf(" %d(이)가 승리했습니다!\n", player + 1);
                break;
            }

            // 플레이어를 바꾼다
            player = 1 - player;  // 0과 1을 번갈아가며
        }

        // 게임 재시작 여부 확인
        printf("게임을 다시 시작하시겠습니까? (1: 예, 0: 아니오): ");
        scanf("%d", &restart);  // 예 아니오 입력받기
    } while (restart == 1);

    // 게임 종료
    printf("게임을 종료합니다.\n");
    return 0;
}
```
