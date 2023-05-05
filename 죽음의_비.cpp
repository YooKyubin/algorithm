#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Pos{
    int idx;
    int x;
    int y;
    char name;

    int operator-(const Pos& a){
        return abs(x - a.x) + abs(y - a.y);
    }
};
struct Player{
    int h;
    int d;
    Pos pos;
};

int n, h, d;
int minTotalDist = 250001;
vector<string> board;
vector<Pos> nodes;
vector<bool> visited;
Pos arrivalPos, startPos;

bool checkArrival(Player player){
    int dist = player.pos - arrivalPos;
    return player.h + player.d >= dist;
}

void DFS(Player player, int totalDist){

    if (checkArrival(player)){ // 남은 h와 d로 E까지 갈 수 있다면 굳이 DFS로 가지 않고 바로 간다, 최단거리를 구하는 것이기 때문에
        int dist = player.pos - arrivalPos;
        minTotalDist = min(minTotalDist, totalDist + dist);
        return;
    }else if (player.pos.name == 'U'){
        player.d = d - 1; // 우산 들자마자 비 한방 맞음
    }

    Pos& pos = player.pos;
    for (int i=0; i < nodes.size(); i++){
        Pos nextNode = nodes[i];
        int nextIdx = nextNode.idx;
        int dist = pos - nextNode;

        if ( player.h + player.d < dist ) continue;
        if ( visited[nextIdx] ) continue;
        
        int nexth = player.h;
        if (player.d < dist) {
            // 다음 목적지는 우산 혹은 도착지점이기 때문에 가는 동안은 비를 맞지만 목적지에 도착하면 우산을 들든 비가 안오든 그래서 한방은 안맞음
            nexth = player.h - (dist - player.d) + 1; 
        }

        visited[nextIdx] = true;
        DFS({nexth, player.d, nextNode}, totalDist + dist);
        visited[nextIdx] = false;
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    Player player;
    cin >> n >> h >> d;
    board.assign(n, "");
    int cnt = 0;

    for(int i=0; i<n; i++){
        cin >> board[i];
        for (int j=0; j<n; j++){
            if (board[i][j] == '.') continue;

            else if (board[i][j] == 'S') {
                startPos = {cnt, i, j, 'S'};
                nodes.push_back(startPos);
            }
            else if (board[i][j] == 'E') {
                arrivalPos = {cnt, i, j, 'E'};
                nodes.push_back(arrivalPos);
            }
            else if (board[i][j] == 'U') {
                nodes.push_back({cnt, i, j, 'U'});
            }
            cnt++;
        }
    }

    visited = vector<bool> (nodes.size(), false);

    player.h = h;
    player.d = 0;
    player.pos = startPos;
    visited[startPos.idx] = true;
    DFS(player, 0);
    
    if (minTotalDist == 500 * 500 +1) minTotalDist = -1;
    cout << minTotalDist << endl;
    
    return 0;
}