#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int x;
    int y;
    int numberOfWallsBroken;
};

int n, m;
vector<vector<char>> board;
vector<pair<int, int>> dir { {0,1}, {1, 0}, {-1, 0}, {0, -1} };

int min(int a, int b) { return a < b ? a : b; }

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    board.resize(n, vector<char>(m));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> board[i][j];
        }
    }

    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(2, INT32_MAX)));
    queue<Node> q;
    q.push({0, 0, 0});
    dist[0][0][0] = 1;

    while (!q.empty())
    {
        int x = q.front().x;
        int y = q.front().y;
        int numberOfWallsBroken = q.front().numberOfWallsBroken;
        q.pop();

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if ( OOB(nx, ny) )
            {
                continue;
            }

            if (board[nx][ny] == '1')
            {
                if (numberOfWallsBroken >= 1)
                    continue;

                if (dist[x][y][numberOfWallsBroken]+1 < dist[nx][ny][numberOfWallsBroken+1])
                {
                    q.push({nx, ny, numberOfWallsBroken + 1});
                    dist[nx][ny][numberOfWallsBroken+1] = dist[x][y][numberOfWallsBroken] + 1;
                }
            }
            else
            {
                if (dist[x][y][numberOfWallsBroken]+1 < dist[nx][ny][numberOfWallsBroken])
                {
                    q.push({nx, ny, numberOfWallsBroken});
                    dist[nx][ny][numberOfWallsBroken] = dist[x][y][numberOfWallsBroken] + 1;
                }
            }
        }
    }

    int answer = INT32_MAX;
    for (auto d : dist[n-1][m-1])
    {
        answer = min(answer, d);
    }

    if (answer == INT32_MAX)
        answer = -1;

    cout << answer << endl;
    return 0;
}