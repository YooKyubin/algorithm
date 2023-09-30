#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<pair<int, int>> sharks;
vector<vector<int>> board;
vector<pair<int, int>> dir { {1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1, 1}, {-1, 0}, {-1,-1} };
vector<vector<int>> dist;

int max(int a, int b) { return a > b ? a : b; }

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int main()
{
    cin >> n >> m;
    board.resize(n, vector<int>(m));
    dist.resize(n, vector<int>(m, INT32_MAX));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            int temp;
            cin >> temp;
            board[i][j] = temp;
            if (temp == 1)
            {
                sharks.push_back({i, j});
            }
        }
    }

    // bfs
    queue<pair<int, int>> q;
    for (auto shark : sharks)
    {
        q.push(shark);
        dist[shark.first][shark.second] = 0;
    }

    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (auto d : dir)
        {
            int nx = cx + d.first;
            int ny = cy + d.second;

            if (OOB(nx, ny))
                continue;

            if (dist[nx][ny] <= dist[cx][cy] + 1)
                continue;

            dist[nx][ny] = dist[cx][cy] + 1;
            q.push({nx, ny});
        }
    }
    int maxVal = 0;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            maxVal = max(maxVal, dist[i][j]);
        }
    }

    cout << maxVal << endl;
    return 0;
}