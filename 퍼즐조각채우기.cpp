#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void rotatate(vector<pair<int,int>>& shape){
    for (int i=0; i < shape.size(); i++){
        int x = shape[i].first;
        int y = shape[i].second;

        shape[i].first = -y;
        shape[i].second = x;
    }
}

bool checkBoundary(int length, int i, int j){
    if (0 <= i && i < length && 0 <= j && j < length){
        return true;
    }
    else{
        return false;
    }
}

void dfs(pair<int, int> start, pair<int, int> v,
    vector<vector<int>>& table, vector<pair<int,int>>& stck, int check) {

    vector<int> dx {1, -1, 0, 0};
    vector<int> dy {0, 0, 1, -1};

    int si = start.first;
    int sj = start.second;
    int i = v.first;
    int j = v.second;
    table[i][j] = check ? 0 : 1;
    stck.push_back({i-si, j-sj});

    for (int d=0; d < 4; d++){
        int ni = i + dx[d];
        int nj = j + dy[d];
        if (checkBoundary(table.size(), ni, nj) && table[ni][nj] == check) {
            dfs(start, {ni,nj}, table, stck, check);
        }
    }
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0;
    cout << table.size() << endl;
    vector<vector<pair<int,int>>> table_index;
    for (int i=0; i < table.size(); i++){
        for (int j=0; j < table[i].size(); j++){
            if (table[i][j] == 1){
                pair<int, int> v {i,j};
                vector<pair<int,int>> stck;
                dfs(v, v, table, stck, 1);
                table_index.push_back(stck);
            }
        }
    }
    for (auto& i: table_index){
        sort(i.begin(), i.end());
    }
    // 단순 출력
    for (auto& idx: table_index){
        for (auto i: idx){
            printf("(%d, %d), ", i.first, i.second);
        }
        cout << endl;
    }
    cout << "done table_index" << endl;

    vector<vector<pair<int,int>>> blank_index;
    for (int i=0; i < game_board.size(); i++){
        for (int j=0; j < game_board[i].size(); j++){
            if (game_board[i][j] == 0){
                pair<int, int> v {i,j};
                vector<pair<int,int>> stck;
                dfs(v, v, game_board, stck, 0);
                blank_index.push_back(stck);
            }
        }
    }
    for (auto& i: blank_index){
        sort(i.begin(), i.end());
    }
    for (auto idx: blank_index){
        for (auto i: idx){
            printf("(%d, %d), ", i.first, i.second);
        }
        cout << endl;
    }

    cout << "done: blank_index" << endl;
    cout << "table index len: " << table_index.size() << endl;
    cout << "blank index len: " << blank_index.size() << endl;
    vector<bool> table_visited(table_index.size(), false);
    vector<bool> blank_visited(blank_index.size(), false);
    for (int t=0; t < table_index.size(); t++){
        for (int b=0; b < blank_index.size(); b++){
            if (!table_visited[t] && !blank_visited[b] && table_index[t].size() == blank_index[b].size()){
                int shape_len = table_index[t].size();
                for (int r=0; r < 4; r++){
                cout << "t: " << t << ", b: " << b << endl;
                    bool correction = true;
                    if (t==38 && b ==35) cout << "error dectection1" << endl;
                    int gapx = table_index[t][0].first - blank_index[b][0].first;
                    if (t==38 && b ==35) cout << "error dectection2" << endl;
                    int gapy = table_index[t][0].second - blank_index[b][0].second;
                    if (t==38 && b ==35) cout << "error dectection3" << endl;

                    for (int i=0; i < shape_len; i++){
                        if (table_index[t][i].first != (blank_index[b][i].first + gapx) || 
                            table_index[t][i].second != (blank_index[b][i].second + gapy)){
                            correction = false;
                            break;
                        }
                    }
                    if (correction){
                        table_visited[t] = true;
                        blank_visited[b] = true;
                        break;
                    }
                    rotatate(table_index[t]);
                    // cout << "before sort" << endl;
                    sort(table_index[t].begin(), table_index[t].end());
                    // cout << "after sort" << endl;
                }
            }
        }
    }

    cout << "table_visited : ";
    for (auto i: table_visited){
        cout << i << ", ";
    } cout << endl;

    cout << "blank_visited : ";
    for (auto i: blank_visited){
        std::cout << i << ", ";
    } cout << endl;

    for (int i=0; i < table_visited.size(); i++){
        if (table_visited[i]){
            answer += table_index[i].size();
        }
    }
    
    return answer;
}

int main() {
    // vector<vector<int>> game_board {
    //     {{0,0,0},{1,1,0},{1,1,1}}
    // };
    // vector<vector<int>> table {
    //     {{1,1,1},{1,0,0},{0,0,0}}
    // };
    vector<vector<int>> game_board {
        {0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0},
        {1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1}, 
        {0,1,1,1,0,0,1,0,1,0,0,1,1,0,1,0,0,0}, 
        {0,0,0,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0}, 
        {0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,1,1,1}, 
        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0}, 
        {0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,0,0,1}, 
        {1,1,1,0,0,0,1,1,0,0,1,0,0,0,0,1,1,0}, 
        {0,0,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,0}, 
        {1,1,0,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1}, 
        {0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0}, 
        {1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,0,1,0}, 
        {0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,1,0,0}, 
        {1,0,1,1,0,1,1,0,0,0,1,0,0,0,1,0,0,1}, 
        {1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,1,1,0}, 
        {0,1,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0}, 
        {0,0,0,1,0,1,0,1,0,0,1,1,1,1,1,1,1,0}, 
        {0,1,0,1,1,0,0,1,0,1,0,0,0,0,0,0,1,0}
    };
    vector<vector<int>> table {
        {1,1,1,1,1,1,0,1,0,1,1,0,0,1,0,0,1,0}, 
        {0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0}, 
        {1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,1}, 
        {1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0,0,1}, 
        {1,1,1,0,0,0,1,0,1,0,1,0,0,1,0,0,1,1}, 
        {0,0,0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0}, 
        {1,1,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1}, 
        {0,0,1,0,1,1,0,1,0,0,1,0,0,1,0,0,0,0}, 
        {1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,1,1,1}, 
        {1,0,1,0,1,1,1,1,0,1,1,0,0,0,1,1,1,0}, 
        {1,1,0,1,0,0,0,0,1,0,0,1,1,1,0,0,0,0}, 
        {0,0,1,1,1,1,0,1,1,0,1,0,0,0,1,1,0,1}, 
        {1,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1}, 
        {1,1,0,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1}, 
        {0,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1,0,0}, 
        {1,1,1,0,1,0,0,1,0,1,1,0,0,1,0,1,0,1}, 
        {0,0,0,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1}, 
        {0,1,1,1,1,0,0,1,0,0,1,1,0,1,0,0,1,1}
    };
    // vector<vector<int>> game_board {
    //     {1,1,0,0,1,0},
    //     {0,0,1,0,1,0},
    //     {0,1,1,0,0,1},
    //     {1,1,0,1,1,1},
    //     {1,0,0,0,1,0},
    //     {0,1,1,1,0,0}
    // };
    // vector<vector<int>> table {
    //     {1,0,0,1,1,0},
    //     {1,0,1,0,1,0},
    //     {0,1,1,0,1,1},
    //     {0,0,1,0,0,0},
    //     {1,1,0,1,1,0},
    //     {0,1,0,0,0,0}
    // };
    cout << solution(game_board, table) << endl;
    return 0;
}

/*
table에서 먼저 도형을 다 찾고 각 도형의 시작점(첫 발견점)을 원점(0,0)으로 하는 상대[i][j]값을 가지는 배열을 만들어서 도형에 저장
game_board에서 똑같이 dfs 돌려서 빈곳 찾기
visited 도 두개 만들어서 관리 
table_index, blank_index, table_visited, blank_visited
    - table 과 blank는 서로 길이가 다를 수 있음.
    - 인덱스를 유의해서 문제를 풀어야함, 개고생했음
정렬하고 가장 첫 좌표를 서로 비교해서 평행이동시키면 되지 않을까?

*/