#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Pos {
    int x;
    int y;

    bool operator==(const Pos input) const {
        return (x == input.x && y == input.y);
        // return (this->x == input.x && this->y == input.y);
    }
    bool operator==(Pos input){
        return (x == input.x && y == input.y);
        // return (this->x == input.x && this->y == input.y);
    }
    Pos operator+(Pos input){
        return { x + input.x, y + input.y} ;
    }
    bool operator<(Pos input){
        if ( x == input.x ){
            return y < input.y;
        }
        else {
            return x < input.x;
        }
    }
};
struct Group {
    Pos startPos;
    int size;
    vector<Pos> wayToLive;

    void init(Pos start){
        startPos = start;
        size = 1;
    }
};


vector<Pos> dir { {0,1}, {1,0}, {-1, 0}, {0, -1} };
int n,m;
vector<vector<int>> mtx;

bool cmp (Pos& a, Pos&b) { return a < b; }
bool OOB (Pos& input) { return input.x < 0 || input.x >= n || input.y < 0 || input.y >= m; }
Pos int2Pos (int i) { return { i / n, i % m}; }

Group bfs(Pos start, vector<vector<bool>>& visited){ //initGroup
    Group group;
    group.init(start);

    queue<Pos> q;
    q.push(start);
    visited[start.x][start.y] = true;

    vector<vector<bool>> wayToLiveVisited(n, vector<bool>(m, false));

    while (!q.empty()) {
        Pos v = q.front();
        q.pop();

        for (Pos d: dir){
            Pos next = v + d;
            if (OOB(next)) continue;
            if (visited[next.x][next.y]) continue;

            if ( mtx[next.x][next.y] == 2 ) {
                group.size += 1;
                q.push(next);
                visited[next.x][next.y] = true;
            }
            else if (mtx[next.x][next.y] ==  0) {
                // 숨구멍의 중복을 없애야 한다.
                group.wayToLive.push_back(next);
            }
        }
    }
    // 숨구멍 중복 제거 및 정렬
    sort( group.wayToLive.begin(), group.wayToLive.end(), cmp );
    group.wayToLive.erase(unique(group.wayToLive.begin(), group.wayToLive.end()), group.wayToLive.end());
    return group;
}

vector<Group> findGroups(){
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<Group> groups;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (visited[i][j]) continue;
            if (mtx[i][j] != 2) continue;
            // groups.push_back( bfs({i, j}, visited) );
            Group temp = bfs({i, j}, visited);
            if (temp.wayToLive.size() <= 2){
                groups.push_back(temp);
            }
        }
    }
    return groups;
}

bool checkWayToLive(Pos fir, Pos sec, Group& group){
    if (group.wayToLive.size() == 1){
        Pos wayToLive = group.wayToLive[0];
        return (fir == wayToLive || sec == wayToLive);
    }
    else { // (group.wayToLive.size() == 2)
        return fir == group.wayToLive[0] && sec == group.wayToLive[1];
    }
}

int bruteForce(vector<Group>& groups){
    int totalMax = 0;
    for (int i=0; i < n*m; i++){
        for (int j=i+1; j < n*m; j++){
            int death = 0;
            Pos fir = int2Pos(i);
            Pos sec = int2Pos(j);

            for (auto group : groups){
                // cout << group.wayToLive.size() << endl;
                if (checkWayToLive(fir, sec, group)){
                    death += group.size;
                }
            }
            totalMax = max(totalMax, death);
        }
    }
    return totalMax;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    mtx.assign(n, vector<int>(m, 0));
    for (int i=0; i < n; i++){
        for (int j=0; j < m; j++){
            cin >> mtx[i][j];
        }
    }
    vector<Group> groups = findGroups();
    cout << bruteForce(groups) << endl;
    return 0;
}

/*
그룹 찾기
    - 2로된 그룹을 나누고 그 그룹의 숨구멍을 찾는다. 
    - 숨구멍이 2개 이하라면 후보에 넣는다. => 나중에 확인하면 되니까 일단 그룹s 에 다 넣어
    - 2개의 숨구멍을 또 다른 배열에 넣는다.
    - 그룹의 속성으로 그룹의 크기, 숨구멍 위치

숨구멍 배열에 들어있는 숨구멍들에 대해서 모든 경우의 수를 구한다.
    - 사실 20 x 20이라 완전 탐색 돌려도 되긴 할듯?
    - 근데 hard 에서는 1000 x 1000 이라 중복 제거한 글로벌 숨구멍 배열을 만들어야 할 지 고민임
for i=0 i:n, for j=i j:n
각 경우마다 후보에 있는 그룹들이 죽는 돌인지 아닌지 판단한다. (숨구멍의 위치를 비교하면 될듯)
각 경우마다 죽는 돌의 개수의 총합을 비교
*/