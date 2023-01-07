#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool checkBoundary(int x, int y){
    if (0 < x && x < 102 && 0 < y && y < 102){
        return true;
    }
    else{
        return false;
    }
}

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    for (int i=0; i < rectangle.size(); i++){
        for (int j=0; j < rectangle[i].size(); j++){
            rectangle[i][j] *= 2;
            cout << rectangle[i][j] << " ";
        }
        cout << endl;
    }
    characterX = characterX * 2;
    characterY = characterY * 2;
    itemX = itemX * 2;
    itemY = itemY * 2;

    vector<int> dx {-1, 1, 0, 0};
    vector<int> dy {0, 0, -1, 1};

    // map 초기화
    vector<vector<int>> map {102,vector<int>(102, -1)}; // 사각형 외부
    for (auto& rec: rectangle){
        for (int i=rec[0]; i < rec[2]+1; i++){
            for (int j=rec[1]; j < rec[3]+1; j++){
                map[i][j] = 1; // 사각형 내부
            }
        }
    }

    // map 그리기
    for (int i=80; i < 101; i++){
        for (int j=80; j < 101; j++){
            printf("%3d ", map[i][j]);
            // cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    for (int i=0; i < 101; i++){
        for (int j=0; j < 101; j++){
            if (map[i][j] == 1){
                for (int d=0; d < 4; d++){
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (checkBoundary(ni, nj) && map[ni][nj] == -1){
                        map[i][j] = 0; // 사각형 변
                        break;
                    }
                    // 대각선 방향 검사
                    ni = i + dx[d/2];
                    nj = j + dy[ 3 - (d%2) ];
                    if (checkBoundary(ni, nj) && map[ni][nj] == -1){
                        map[i][j] = 0;
                        break;
                    }
                }
            }
        }
    }

    // map 그리기
    for (int i=80; i < 101; i++){
        for (int j=80; j < 101; j++){
            printf("%3d ", map[i][j]);
            // cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // bfs
    queue<vector<int>> q;
    q.push({characterX, characterY});
    while (!q.empty()) {
        int vx = q.front()[0];
        int vy = q.front()[1];
        q.pop();

        for (int d=0; d < 4; d++){
            int ni = vx + dx[d];
            int nj = vy + dy[d];
            if (checkBoundary(ni, nj) && map[ni][nj] == 0){
                map[ni][nj] = map[vx][vy] + 1;
                q.push({ ni, nj });
            }
        }
    }

    // map 그리기
    for (int i=100; i < 101; i+=2){
        for (int j=0; j < 101; j++){
            printf("%3d ", map[i][j]);
            // cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << map[itemX][itemY] << endl;;
    return map[itemX][itemY] / 2;
}

int main() {
    vector<vector<int>> rectangle {{1,1,50,50}};
    int32_t characterX = 1;
    int32_t characterY = 1;
    int itemX = 50;
    int itemY = 50;
    // vector<vector<int>> rectangle {{1,1,3,7},{2,2,7,4},{4,3,6,6}};
    // int32_t characterX = 1;
    // int32_t characterY = 2;
    // int itemX = 6;
    // int itemY = 6;
    // vector<vector<int>> rectangle {{2, 1, 3, 6}, {4, 1, 5, 6}, {1, 2, 6, 3}, {1, 4, 6, 5}};
    // int32_t characterX = 3;
    // int32_t characterY = 2;
    // int itemX = 5;
    // int itemY = 4;
    // vector<vector<int>> rectangle {{1,1,7,4},{3,2,5,5},{4,3,6,9},{2,6,8,8}};
    // int32_t characterX = 1;
    // int32_t characterY = 3;
    // int itemX = 7;
    // int itemY = 8;

    cout << solution(rectangle, characterX, characterY, itemX, itemY) << endl;
    return 0;
}