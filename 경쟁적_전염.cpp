#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Pos {
    int x;
    int y;

    Pos operator+ (Pos input){
        return { x + input.x, y + input.y };
    }
};

struct Node {
    int val;
    int sec;
    Pos pos;
};

int n, k, s, x, y;
vector<Pos> dir { {0,1}, {1,0}, {-1,0}, {0,-1} };
vector<vector<int>> tube;

bool OOB(Pos input){ return input.x < 0 || input.x >= n || input.y < 0 || input.y >=y; }

void bfs(vector<vector<Node>>& order, int sec) {
    queue<Node> q;
    for (int i=0; i < k+1; i++){
        for (auto node: order[i]){
            q.push(node);
        }
    }

    while (!q.empty() && q.front().sec < sec){
        Node v = q.front();
        q.pop();

        for (auto d : dir){
            Pos nextPos = v.pos + d;
            if ( OOB(nextPos) ) continue;
            if ( tube[nextPos.x][nextPos.y] == 0) {
                q.push( { v.val, v.sec+1, nextPos });
                tube[nextPos.x][nextPos.y] = v.val;
            }
        }
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    vector<vector<Node>> order(k+1);
    tube.assign(n, vector<int>(n, 0));

    for (int i=0; i <n; i++){
        for (int j=0; j < n; j++){
            cin >> tube[i][j];
            if (tube[i][j] != 0) {
                int val = tube[i][j];
                order[val].push_back({ val, 0, {i,j} });
            }
        }
    }
    cin >> s >> x >> y;

    bfs(order, s);
    cout << tube[x-1][y-1] << endl;
    return 0;
}