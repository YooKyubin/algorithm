#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos{
    int x;
    int y;

    bool operator==(Pos input){
        return input.x == x && input.y == y;
    }
    Pos operator+(Pos input){
        Pos res;
        res.x = input.x + this->x;
        res.y = input.y + this->y;
        return res;
    }
};

vector<Pos> dir { {0,1}, {1,0}, {-1, 0}, {0, -1} };

int w, h;
vector<vector<bool>> visited;
vector<vector<int>> dist;
vector<vector<bool>> isWall;

bool OOB(Pos input){
    return input.x < 0 || input.x >= h || input.y < 0 || input.y >= w;
}

void bfs(Pos start){
    queue<Pos> q;
    q.push(start);
    dist[start.x][start.y] = 0;
    visited[start.x][start.y] = true;

    while (!q.empty()){
        Pos cur = q.front();
        q.pop();
        for (Pos d: dir){
            Pos next = cur + d;
            while( !( OOB(next) || isWall[next.x][next.y] ) ){
                // if (OOB(next)) break;
                // if (isWall[next.x][next.y]) break;
                if (dist[next.x][next.y] > dist[cur.x][cur.y]+1){
                    dist[next.x][next.y] = dist[cur.x][cur.y]+1;
                    q.push(next);
                }
                // else if (dist[next.x][next.y] == dist[cur.x][cur.y]){
                    
                // }
                // else if (dist[next.x][next.y] < dist[cur.x][cur.y]){
                // }


                next = next + d;
            }
        }
    }
}

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> w >> h;
    vector<Pos> CPos;
    visited = vector<vector<bool>> (h, vector<bool>(w, false));
    dist = vector<vector<int>> (h, vector<int>(w, w*h+1));
    isWall = vector<vector<bool>> (h, vector<bool>(w, false));
    for (int i=0; i<h; i++){
        string input;
        cin >> input;
        for (int j=0; j<w; j++){
            if (input[j] == '*') isWall[i][j] = true;
            if (input[j] == 'C') {
                CPos.push_back( {i,j} );
            }
        }
    }
    dist[CPos[0].x][CPos[0].y] = 0;
    bfs(CPos[0]);
    cout << dist[CPos[1].x][CPos[1].y]-1 << endl;
}