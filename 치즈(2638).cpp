#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int x;
    int y;
    int time;
};

vector<pair<int, int>> dir { {0,1}, {1,0}, {-1,0}, {0, -1} };

int n, m;
vector<vector<int>> board;

int max (int a, int b) { return a > b ? a : b; }

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int bfs()
{
    queue<pair<int, int>> curQ;
    queue<pair<int, int>> nextQ;
    vector<vector<int>> curVisited(n, vector<int>(m, 0));
    vector<vector<int>> nextVisited(n, vector<int>(m, 0));
    nextVisited[0][0] = 2;
    nextQ.push({0, 0});
    int cnt = 0;

    while (!nextQ.empty())
    {
        curQ = nextQ;
        curVisited = nextVisited;

        nextQ = queue<pair<int, int>>();
        nextVisited.assign(n, vector<int>(m, 0));

        while (!curQ.empty())
        {
            int x = curQ.front().first;
            int y = curQ.front().second;
            curQ.pop();

            for (auto d : dir)
            {
                int nx = x + d.first;
                int ny = y + d.second;

                if (OOB(nx, ny))
                    continue;

                if (board[nx][ny] == 0)
                {
                    if (curVisited[nx][ny] == 2)
                        continue;

                    curVisited[nx][ny] = 2;
                    curQ.push({nx, ny});
                }
                else
                {
                    ++curVisited[nx][ny];

                    if (curVisited[nx][ny] == 2)
                    {
                        nextQ.push({nx, ny});
                        nextVisited[nx][ny] = 2;
                        board[nx][ny] = 0;
                    }
                }
            }

        }
        ++cnt;
    }

    return cnt -1;
}

int main()
{
    //freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    board.resize(n, vector<int>(m));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> board[i][j];
        }
    }

    cout << bfs() << endl;

    return 0;
}