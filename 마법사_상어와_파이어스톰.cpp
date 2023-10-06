#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int n, q;
int powerN;
vector<vector<int>> board;
vector<int> arrL;
vector<int> dx {0, 0, -1, 1};
vector<int> dy {-1, 1, 0, 0};

bool OOB(int x, int y)
{
    return x < 0 || x >= powerN || y < 0 || y >= powerN;
}

vector<vector<int>> rotate(int offset)
{
    vector<vector<int>> ret(powerN, vector<int>(powerN));

    for (int i=0; i<powerN; i += offset)
    {
        for (int j=0; j<powerN; j += offset)
        {
            
            for (int localI = 0; localI<offset; ++localI)
            {
                for (int localJ =0; localJ<offset; ++localJ)
                {
                    ret[localJ + i][-localI + offset-1 + j] = board[localI + i][localJ + j];
                }
            }
        }
    }

    return ret;
}

void melt()
{
    vector<vector<int>> ret = board;
    for (int i=0; i<powerN; ++i)
    {
        for (int j=0; j<powerN; ++j)
        {
            int zeroCnt = 0;
            
            if (board[i][j] == 0)
                continue;
            
            for (int d=0; d<4; ++d)
            {
                int nx = i + dx[d];
                int ny = j + dy[d];

                if (OOB(nx, ny) || board[nx][ny] == 0)
                    ++zeroCnt;

            }

            if (zeroCnt > 1)
                --ret[i][j];

        }
    }
    board = ret;
}

int bfs(int x, int y, vector<vector<bool>>& visited)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    int cnt = 1;
    visited[x][y] = true;
    
    while (!q.empty())
    {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int d=0; d<4; ++d)
        {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (OOB(nx, ny))
                continue;

            if (visited[nx][ny])
                continue;
            
            if (board[nx][ny] == 0)
                continue;

            visited[nx][ny] = true;
            q.push({nx, ny});
            cnt++;
        }
    }

    return cnt;
}

int main()
{
    cin >> n >> q;
    powerN = (int)pow(2, n);
    board.resize(powerN, vector<int>(powerN));
    for (int i=0; i< powerN; ++i)
    {
        for (int j=0; j < powerN; ++j)
        {
            cin >> board[i][j];
        }
    }
    for (int i =0; i<q; ++i)
    {
        int L;
        cin >> L;
        arrL.push_back(L);
    }

    for (int L : arrL)
    {
        int powerL = pow(2, L);
        board = rotate(powerL);
        melt();
    }

    int sum = 0;
    int maxCnt = 0;
    vector<vector<bool>> visited(powerN, vector<bool>(powerN, false));
    for (int i=0; i<powerN; ++i)
    {
        for (int j=0; j<powerN; ++j)
        {
            sum += board[i][j];

            if (visited[i][j] || board[i][j] == 0)
                continue;

            maxCnt = max(maxCnt, bfs(i, j, visited));
        }
    }

    cout << sum << endl;
    cout << maxCnt << endl;

    return 0;
}

/*
 0    1     x
-1    0     y = (y , -x) => (y, -x + offset);
*/