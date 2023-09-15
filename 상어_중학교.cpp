#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<vector<int>> board;

vector<pair<int, int>> dir { {0,1}, {0,-1}, {1,0}, {-1,0} };

bool OOB(int x, int y) { return x < 0 || x >= n || y < 0 || y >= n; }
int max(int a, int b) { return a > b ? a : b; }

vector<pair<int, int>> bfs(int x, int y, vector<vector<bool>>& visited, int& rainbowCnt)
{
    vector<pair<int, int>> ret;
    int color = board[x][y];
    vector<pair<int, int>> rainbow;
    queue<pair<int, int>> q;

    q.push({x, y});
    ret.push_back({x, y});
    visited[x][y] = true;

    while (!q.empty())
    {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        for (auto d: dir)
        {
            int nX = d.first + curX;
            int nY = d.second + curY;

            if (OOB(nX, nY) || visited[nX][nY])
                continue;

            if (board[nX][nY] != 0 && board[nX][nY] != color)
                continue;

            if (board[nX][nY] == 0) // 무지개 블록은 bfs 탐색 후에 다른 색상의 블록이 사용할 수 있도록 visited = false로 변경해주어야한다.
                rainbow.push_back({nX, nY});
            visited[nX][nY] = true;
            ret.push_back({nX, nY});
            q.push({nX, nY});
        }
    }
    for (auto rb : rainbow)
        visited[rb.first][rb.second] = false;

    rainbowCnt = rainbow.size();
    return ret;
}

vector<pair<int, int>> findBlock(pair<int, int>& pos) // return blockSize, pos = 블럭의 기준 위치
{
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<pair<int, int>> selected;
    int selectedRainbow = 0;
    
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            if (board[i][j] < 1) // 무지개, 검정 블록, -2는 비어있는 칸으로 처리
                continue;

            if (visited[i][j])
                continue;
            
            int bufferRainbow = 0;
            vector<pair<int, int>> buffer = bfs(i, j, visited, bufferRainbow);

            if (buffer.size() < selected.size())
                continue;
            if (buffer.size() == selected.size())
            {
                if (bufferRainbow < selectedRainbow)
                    continue;
            }

            selected = buffer;
            pos = {i, j};
            selectedRainbow = bufferRainbow;
        }
    }

    return selected;
}

int deletBlock(vector<pair<int, int>> blocks)
{
    int ret = 0;
    for (auto block : blocks)
    {
        int x = block.first;
        int y = block.second;

        board[x][y] = -2;
        ++ret;
    }

    return ret * ret;
}

void gravity()
{
    for (int i=n-1; i >=0; --i)
    {
        for (int j=n-1; j>=0; --j)
        {
            if (board[i][j] < 0) // -1, -2 인 경우 넘어간다.
                continue;;

            int height = n-1;
            for (int h=i+1; h<n; ++h)
            {
                if (board[h][j] != -2)
                {
                    height = h-1;
                    break;
                }
            }
            
            if (height != i)
            {
                board[height][j] = board[i][j];
                board[i][j] = -2;
            }
        }
    }
}

void rotate()
{
    vector<vector<int>> temp(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            temp[i][j] = board[j][-i+n-1];
        }
    }

    board = temp;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    board.resize(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> board[i][j];
        }
    }
    
    int score = 0;
    while (true)
    {
        // find large block
            // block size < 2 : break;
        pair<int, int> pos;
        vector<pair<int, int>> blocks = findBlock(pos);
        if (blocks.size() < 2)
            break;
        
        // delet block, add score
        score += deletBlock(blocks);

        // gravity
        gravity();

        // rotate
        rotate();

        // gravity
        gravity();
    
    }

    cout << score << endl;
    return 0;
}

/*
기준 블록: 무지개가 아닌 행이 가장 작고, 열이 가장 작은 블록
찾을 블록: 크기가 가장 큰 블록 중, 행이 가장 크고 열이 가장 큰 블록
격자는 반시계 회전
*/