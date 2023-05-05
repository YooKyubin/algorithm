#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Pos{
    int x;
    int y;
};
struct Player{
    int h;
    int d;
    Pos pos;
};

int n, h, d;
int answer = -1;
vector<string> map;
vector<vector<int>> dist;
vector<vector<int>> visited;
vector<Pos> delta { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
queue<Player> q;

bool OOB(Pos p){ 
    return (p.x < 0 || p.x >= n) || (p.y < 0 || p.y >= n); 
}

void BFS(Player start){
    q.push(start);
    while(!q.empty()){
        Player player = q.front();
        Pos& v = player.pos;
        q.pop();

        if (map[v.x][v.y] == 'U'){
            player.d = d;
        }
        else if(map[v.x][v.y] == 'E'){
            answer = dist[v.x][v.y];
            break;
        }
        
        player.d == 0 ? player.h -= 1 : player.d -= 1;

        for(auto del: delta){
            int nx = del.x + v.x;
            int ny = del.y + v.y;

            if( OOB({nx, ny}) ) continue;
            if( visited[nx][ny] >= player.h + player.d ) continue;
            if( player.h == 0 ) continue;

            visited[nx][ny] = player.h + player.d;
            dist[nx][ny] = dist[v.x][v.y] + 1;
            q.push({ player.h, player.d, {nx, ny} });
        }
    }
}


int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    Player player;
    cin >> n >> h >> d;
    
    map.assign(n, "");
    // visited.assign(n, vector<int>(n, 0));
    // dist.assign(n, vector<int>(n, 0));
    visited = vector(n, vector<int>(n, 0));
    dist = vector(n, vector<int>(n, 0));
    Pos startPos;

    for(int i=0; i<n; i++){
        cin >> map[i];
        for (int j=0; j<n; j++){
            if (map[i][j] == 'S') {
                startPos.x = i;
                startPos.y = j;
            }
        }
    }

    player.h = h+1; // 시작할 때는 비를 맞지 않음, BFS에 항상 현재 위치에(pop 하는 경우에) 비를 맞도록 설정했음 따라서 S부분하게 비를 맞으면 안되는 상황에서 맞는 부분을 하나 빼줌
    player.d = 0;
    player.pos = startPos;
    
    BFS(player);
    
    cout << answer << endl;
    return 0;
}