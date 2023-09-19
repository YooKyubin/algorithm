#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct State
{
    int x;
    int y;
    int k=0;
};

int n, m, k;
vector<vector<char>> map;
vector<vector<vector<int>>> dist;
vector<int> dx {0, 0, -1, 1};
vector<int> dy {1, -1, 0, 0};

int min(int a, int b) { return a < b ? a : b; }

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    map.resize(n, vector<char>(m));
    dist.resize(n, vector<vector<int>>(m, vector<int>(k+1, 0))); // map[i][j]까지 가기위해 k 개 벽을 부순상태
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> map[i][j];
        }
    }

    queue<State> q;
    q.push({0,0,0});
    dist[0][0][0] = 1; // 출발지점도 카운트에 포함

    while (!q.empty())
    {
        int cx = q.front().x;
        int cy = q.front().y;
        int ck = q.front().k;
        q.pop();
        
        for (int d=0; d<4; ++d)
        {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (OOB(nx, ny))
                continue;

            if (map[nx][ny] == '0')
            {
                if (dist[nx][ny][ck] != 0)
                    continue;

                q.push({nx, ny, ck});
                dist[nx][ny][ck] = dist[cx][cy][ck] + 1;
            }
            else 
            {
                if (ck >= k)
                    continue;
        
                if (dist[nx][ny].at(ck+1) != 0)
                    continue;

                q.push({nx, ny, ck+1});
                dist[nx][ny][ck+1] = dist[cx][cy][ck] + 1;

            }
        }
    }
    
    int answer = INT32_MAX;
    for (auto a : dist[n-1][m-1])
    {
        if (a == 0)
            continue;

        answer = min(a, answer);
    }
    if (answer == INT32_MAX)
        answer = -1;

    cout << answer << endl;
    
    return 0;
}