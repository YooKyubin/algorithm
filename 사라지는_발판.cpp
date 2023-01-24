#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};
int width;
int height;

bool checkBoundary(int x, int y){
    return (0 <= x && x < height && 0 <= y && y < width);
}

int dfs(vector<int> cur, vector<int> opposite, vector<vector<int>>& board){
    int curx = cur[0];
    int cury = cur[1];
    int max_result = 0;
    int min_result = (1 << 30);
    if (board[curx][cury] == 0){
        return 0; // 겜 끝! 졋음
    }
    
    bool win = false; // for 문을 돌지못하면 움직일 수 없는 거니까 진거임
    for (int d=0; d < 4; d++){
        int nx = curx + dx[d];
        int ny = cury + dy[d];

        if (checkBoundary(nx, ny) && board[nx][ny] == 1){
            printf("curx: %d, cury: %d, nx: %d, ny: %d \n", curx, cury, nx, ny);
            board[curx][cury] = 0;
            int step = dfs(opposite, {nx, ny}, board) + 1;
            board[curx][cury] = 1;

            if (step % 2 == 1){ // 미래에서 너 이긴대 겜 빨리 끝내
                win = true;
                min_result = min_result < step ? min_result : step;
                cout << "check" << endl;
            }
            else {
                max_result = max_result < step ? step : max_result;
                cout << "c212121213" << endl;
            }
        }
    }
    return win ? min_result : max_result;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {
    int answer = 0;
    height = board.size();
    width = board[0].size();
    
    answer = dfs(aloc, bloc, board);
    return answer;
}

int main() {
    vector<vector<int>> board {{1,1,1}, {1,1,1}, {1,1,1}};
    vector<int> aloc {1, 0};
    vector<int> bloc {1, 2};
    cout << solution(board, aloc, bloc) << endl;
    return 0;
}

/*
승리:
    - 내 차례인데 나와 상대가 같은 자리에 있는 경우
패배:
    - 내 차례인데 내가 움직일 곳이 없는 경우
    - 내 차례인데 내가 밟고 있는 발판이 사라진 경우
게임이 끝났을 때 누가 이겼는지 확인해서 
    내가 이기면 항상 최소값을 고르도록, 상대는 최대값
    내가 지면 항상 최대값을 고르도록, 상대는 최소값

step이 홀수면 => 내가 차례에서 끝남 -> ?? 승리 실패 둘 다 가능인디? -> 그래서 내 차례에서 패배하는 경우만 검사 => 이제 홀수면 진거임
리턴으로 휴리스틱값을 주는 dfs 작성
*/