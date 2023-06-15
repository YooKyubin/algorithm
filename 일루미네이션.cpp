#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
    int x;
    int y;

    bool operator==(Pos input){
        return x == input.x && y == input.y;
    }
    Pos operator+(Pos input){
        Pos res;
        res.x = this->x + input.x;
        res.y = this->y + input.y;
        return res;
    }
};

int w, h;
vector<vector<int>> matrix;
vector<vector<Pos>> nextDir { // 아니 이게 문제에서는 1부터 시작인데 실제 인덱스는 0부터 시작이라 좀 바뀜;
    { {-1, 1}, {0, -1}, {-1, 0}, {1, 0}, {0, 1}, {1, 1} },  // even
    { {-1, -1}, {0, -1}, {-1, 0}, {1, 0}, {0, 1}, {1, -1} } // odd
};
vector<vector<int>> visited;

bool OOB(Pos input){
    return 0 > input.x || input.x >= h || 0 > input.y || input.y >= w;
}

int bfs(Pos start){
    bool isOut = false;
    int wallCnt = 0;

    queue<Pos> q;
    q.push(start);
    visited[start.x][start.y] = true;

    while (!q.empty()){
        Pos cur = q.front();
        q.pop();
        for (Pos d : nextDir[cur.x % 2]){
            Pos next = cur + d;
            if (OOB(next)) isOut = true;
            else if (matrix[next.x][next.y] == 1) wallCnt++;
            else if (!visited[next.x][next.y]){
                visited[next.x][next.y] = true;
                q.push(next);
            }
        }
    }

    if (isOut) return wallCnt;
    else return 0;
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> w >> h;
    int wallCnt = 0;
    matrix = vector<vector<int>> (h, vector<int>(w, 0));
    visited = vector<vector<int>> (h, vector<int>(w, false));
    for (int i=0; i < h; i++){
        for (int j=0; j < w; j++){
            cin >> matrix[i][j];
        }
    }
    for (int i=0; i < h; i++){
        for (int j=0; j < w; j++){
            if (matrix[i][j] == 1) {
                if (i == 0 || i == h-1 || j == 0 || j == w-1){ // 가장자리인 경우 OOB 체크해서 wallCnt++
                    for (Pos d : nextDir[i%2]){
                        Pos next = Pos{i, j} + d;
                        if (OOB(next)) wallCnt++;
                    }
                }
            }
            else {
                if (!visited[i][j]) wallCnt += bfs({i, j});
            }
        }
    }
    cout << wallCnt << endl;
    
    return 0;
}