#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {0, 1}, {1, 0}, {0,-1}, {-1, 0}};

int max(int a, int b) { return a > b ? a : b; }

int n, m;
vector<vector<int>> board;
vector<pair<int, int>> virus;
int zeroCnt = 0;
int answer = 0;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= m;
}

int bfs()
{   
    int maxZero = zeroCnt - 3;
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (pair<int, int> v : virus)
    {
        q.push(v);
        visited[v.first][v.second] = true;
    }

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny))
                continue;

            if (board[nx][ny] != 0)
                continue;
            
            if (visited[nx][ny])
                continue;

            visited[nx][ny] = true;
            q.push({nx, ny});
            --maxZero;
        }
    }

    return maxZero;
}

void setWall (int idx, int cnt, int maxCnt)
{
    if (cnt == maxCnt)
    {
        answer = max(answer, bfs());
        return;
    }

    for (int i=idx; i<n * m; ++i)
    {
        int x = i / m;
        int y = i % m;
        if (board[x][y] != 0)
            continue;

        board[x][y] = 1;
        setWall(i+1, cnt+1, maxCnt);
        board[x][y] = 0;
    }
}

int main()
{   
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n >> m;
    board.resize(n, vector<int>(m));
    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<m; ++j)
        {
            cin >> board[i][j];

            if (board[i][j] == 2)
            {
                virus.push_back({i, j});            
            }
            else if (board[i][j] == 0)
            {
                ++zeroCnt;
            }
        }
    }

    setWall(0, 0, 3);
    cout << answer << endl;

    return 0;
}