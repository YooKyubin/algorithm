#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<pair<int, int>> dir { {0,1}, {1,0}, {-1, 0}, {0, -1} };

int n;
vector<vector<char>> board;

bool OOB(int x, int y) 
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

void bfs(pair<int, int> start, vector<vector<bool>>& visited)
{
    queue<pair<int, int>> q;

    q.push(start);
    visited[start.first][start.second] = true;

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        char cur = board[x][y];

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny))
                continue;
            
            if (visited[nx][ny])
                continue;

            char next = board[nx][ny];
            if(cur == next)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

void deuteranomalyBFS(pair<int, int> start, vector<vector<bool>>& visited)
{
    queue<pair<int, int>> q;

    q.push(start);
    visited[start.first][start.second] = true;

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        char cur = board[x][y];
        if (cur == 'G')
            cur = 'R';

        for (auto d : dir)
        {
            int nx = x + d.first;
            int ny = y + d.second;

            if (OOB(nx, ny))
                continue;
            
            if (visited[nx][ny])
                continue;

            char next = board[nx][ny];
            if (next == 'G')
                next = 'R';

            if(cur == next)
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin >> n;
    board.resize(n, vector<char>(n));
    for(int i=0; i<n; ++i) 
    {
        for (int j=0; j<n; ++j)
        {
            cin >> board[i][j];
        }
    }

    int groupCnt = 0;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            if (visited[i][j])
                continue;

            bfs({i,j}, visited);
            ++groupCnt;
        }
    }

    int deuteranomalyCnt = 0;
    vector<vector<bool>> deuteranomalyVisited(n, vector<bool>(n, false));
    for(int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            if (deuteranomalyVisited[i][j])
                continue;

            deuteranomalyBFS({i,j}, deuteranomalyVisited);
            ++deuteranomalyCnt;
        }
    }
    cout << groupCnt << " " << deuteranomalyCnt << endl;
    return 0;
}