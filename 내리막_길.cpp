#include <iostream>
#include <vector>

#define x first
#define y second

using namespace std;

int n, m;
int answer = 0;
vector<vector<int>> map;
vector<vector<int>> dp;
vector<pair<int, int>> dir = { {1,0}, {0,1}, {-1, 0}, {0, -1} };

bool OOB(int x, int y){
    return x < 0 || x >= n || y < 0 || y >= m;
}

void dfs(int x, int y){
    int ret = 0;
    for (auto d : dir){
        int nx = x + d.x;
        int ny = y + d.y;
        if (OOB(nx, ny)) continue;
        if (map[x][y] <= map[nx][ny]) continue;

        if (dp[nx][ny] == -1) dfs(nx, ny);
        ret += dp[nx][ny];
    }
   dp[x][y] = ret;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    map.assign(n, vector<int>(m, 0));
    for (int i=0; i<n; i++){
        vector<int> temp;
        for (int j=0; j<m; j++){
            cin >> map[i][j];
        }
    }
    dp.assign(n, vector<int>(m, -1));
    dp[n-1][m-1] = 1;

    if (dp[0][0] == -1) dfs(0, 0); // 출발지점이 도착지점인 경우 예외 처리
    cout << dp[0][0] << endl;
    return 0;
}